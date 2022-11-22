#include "Truck.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>



namespace TruckSocket
{

    Truck::~Truck()
    {
        for(auto iter = _Platoon.begin(); iter != _Platoon.end(); ++iter)
            {
                std::cout << "Truck in position : " << iter->first << " with address " << iter->second.first << ":" <<iter->second.second << std::endl;
            //ignore value
            //Value v = iter->second;
            }
        delete myServer;
    }


    Truck::Truck(const std::string& myAddress, int port)
    {

        this->_id = 0;
        this->_speed = 0;
        this->_stearingAngle = 0;
        this->_distance = 0;
        this->_state = TruckState::Available;
        this ->_position = 0;

        this ->myServerAddress.sin_family = AF_INET;
        this ->myServerAddress.sin_port = htons(port);
        this ->myServerAddress.sin_addr.s_addr = INADDR_ANY;

        this->_myAddress = myAddress;
        this->_myPort = port;
        myServer = new std::thread([this]() {TruckServer();});
    }


    Truck::Truck(u_int16_t newID, const std::string& myAddress, int port):_id (newID)
    {
        this->_speed = 0;
        this->_stearingAngle = 0;
        this->_distance = 0;
        this->_state = TruckState::Available;
        this ->_position = 0;
        this ->myServerAddress.sin_family = AF_INET;
        this ->myServerAddress.sin_port = htons(port);
        this ->myServerAddress.sin_addr.s_addr = INADDR_ANY;
        this->_myAddress = myAddress;
        this->_myPort = port;
        myServer = new std::thread([this]() {TruckServer();});
        

    }

    u_int16_t Truck::GetID()
    {
        return _id;
    }

    void Truck::SetID(u_int16_t newID)
    {
        _id = newID;
    }



    speedType Truck::GetSpeed()
    {
        return _speed;
    }

    void Truck::SetSpeed(speedType newSpeed)
    {
        _speed = newSpeed;
    }

    stearingAngleType Truck::GetAngle()
    {
        return _stearingAngle;
    }

    void Truck::SetAngle(stearingAngleType newStearingAngle)
    {
        _stearingAngle = newStearingAngle;
    }

    distanceType Truck::GetDistance()
    {
        return _distance;
    }

    void Truck::SetDistance(distanceType newDistance)
    {
        _distance = newDistance;
    }


    void Truck::SetState(TruckState newState)
    {
        _state = newState;
    }

    TruckState Truck::GetState()
    {
        return _state;
    }
    


    bool Truck::isLeader()
    {
        return _isLeader;
    }

    bool Truck::Send(char* buffer )
    {
        return false;
    }
    bool Truck::Broadcast(const Message& message)
    {
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

        if(sockfd <0)
            return false;
        char buffer[2048];
        message.ToBuffer(buffer);
        memset(&receiver, '\0', sizeof(receiver));
        receiver.sin_family = AF_INET;
        for(auto truck = _Platoon.begin(); truck != _Platoon.end(); ++truck)
        {
            receiver.sin_port = htons(truck->second.second);
            receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
            sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        }

//        printf("[+]Data Send: %s\n", buffer);
        

        close(sockfd);
        return true;

    }
    
    bool Truck::Send(const Message& message, int position)
    {
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        if(sockfd <0)
            return false;
        char buffer[2048];
        message.ToBuffer(buffer);
        memset(&receiver, '\0', sizeof(receiver));

        receiver.sin_family = AF_INET;
        receiver.sin_port = htons(_Platoon[position].second);
        receiver.sin_addr.s_addr = inet_addr(_Platoon[position].first.c_str());
        sendto(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&receiver, sizeof(receiver));

        close(sockfd);
        return true;

    }
    bool Truck::BroadcastInfo()
    {
        
                    Message message;
                    message._Event = Event(EventType::BroadcastInfo);
                    message._ReceiverPosition = BROADCAST;
                    message._SenderPosition = this->_position;

                    std::string  Tags[] = {SPEED, SAFETY_DISTANCE, PLATOON_SIZE};
                    std::string Values[] = {std::to_string(int(_speed)), std::to_string(_safetyDistance), std::to_string(_platoonSize)};

                    message._Body = StupidJSON::CreateJsonFromTags(Tags, Values, 3);
                    //char address[20];
                    //inet_ntop(AF_INET,&myServerAddress.sin_addr.s_addr, address,  20);
                    
                    message._Address=this->_myAddress;
                    message._Port=this->_myPort;
                    bool check = this->Broadcast(message);

                    Send(message, GUI_ADDRESS, GUI_PORT);


                    _lastTimeInfo = time(0);
                    return check;
    }
    bool Truck::Send(const Message& message, const std::string& address, int port)
    {

        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        if(sockfd <0)
            return false;


        char broadcast = '1';
        memset(&receiver, '\0', sizeof(receiver));
        char buffer[2048];
        message.ToBuffer(buffer);
        receiver.sin_family = AF_INET;
        receiver.sin_port = htons(port);
        receiver.sin_addr.s_addr = inet_addr(address.c_str());
        auto a = sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));

        std::cout << a;
        close(sockfd);
        return true;

    }

    bool Truck::SendInfoToInterface( const std::string& InterfaceAddress, int InterfacePort)
    {
        Message message;
        message._Event = Event(EventType::InterfaceInfo);
        message._ReceiverPosition = INTERFACE;
        message._SenderPosition = this->_position;
        std::string  Tags[] = {SPEED, SAFETY_DISTANCE, PLATOON_SIZE};
        std::string Values[] = {std::to_string(int(_speed)), std::to_string(_safetyDistance), std::to_string(_platoonSize)};

        message._Body = StupidJSON::CreateJsonFromTags(Tags, Values, 3);
                    //char address[20];
                    //inet_ntop(AF_INET,&myServerAddress.sin_addr.s_addr, address,  20);
                    
        message._Address=this->_myAddress;
        message._Port=this->_myPort;

        bool check = Send(message, InterfaceAddress, InterfacePort);
        return check;
    }
    void Truck::TruckServer()
    {

        struct sockaddr_in add;
        this->serverSocket=0;
        char buffer[2048];
        socklen_t addr_size;
        int serverSocket = socket(PF_INET, SOCK_DGRAM, 0);

        add.sin_addr.s_addr =inet_addr( this->_myAddress.c_str());
        add.sin_family = AF_INET;
        add.sin_port = htons(this->_myPort);
        
        
        auto a = bind(serverSocket, (struct sockaddr*)&this->myServerAddress, sizeof(myServerAddress));
        std::cout << a<<std::endl;
        while(1)
        {
            struct sockaddr_in si_other;
            addr_size = sizeof(si_other);
            int a = recvfrom(serverSocket, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)& si_other, &addr_size);
            if(a <0)
                std::cout << a;
            printf("[+]Data Received: %s", buffer);
            
            this->lockMessageQueue.lock();
            RawMessageQueue.push(RawMessage(si_other, buffer));
            this->lockMessageQueue.unlock();
            
        }
    }


//trying to check my email
    void Truck::Update()
    {
        switch (_state)
            {
            case TruckState::Available:
                
                break;

            case TruckState::PlatoonMember:
                break;
            case TruckState::Leader:
                if(!_isLeader){
                    _isLeader = true;
                    _speed = 100;
                    BroadcastInfo();
                    return;
                }
                if(difftime( time(0), _lastTimeInfo) > SECONDS_TO_INFO)
                {
                    BroadcastInfo();
                }
                //if null message
                //broadcast info
                break;
            case TruckState::SimpleMember:
                break;

            case TruckState::Unavailable:
                /* code */
                break;
            case TruckState::PlatoonCreation:
                _position = LEADER_POSITION;
                _platoonSize = 1;
                PRINT(" I am the new leader");
                _state = Leader;
                
                break;
            case TruckState::Elections:
                if(_position == NEW_LEADER_POSITION)
                {

                }
                else
                {

                }


            default:
                break;
        }
    }
    void Truck::HandleMessages()
    {
        auto size = MessageQueue.size();
        if(size == 0)
        {
            Update();
            return;
        }
        while(size >0)
        {
            
            auto message = MessageQueue.front();
            MessageQueue.pop();
            size = MessageQueue.size();
            
            if(message._SenderPosition == NULL_POSITION){}
            else if ( _Platoon.find(message._SenderPosition) == _Platoon.end()) {
                _Platoon[message._SenderPosition].first =message._Address;
                _Platoon[message._SenderPosition].second = message._Port;
                _platoonSize++;
            }

            
            // << std::endl<< message._Port<< std::endl ; 
            React(message);
            Update();
            
            

        }
    }
    void Truck::HandleRawMessages()
    {
        this->lockMessageQueue.lock();
        auto size = RawMessageQueue.size();
        this->lockMessageQueue.unlock();
        while(size!=0)
        {
            this->lockMessageQueue.lock();
            auto message = RawMessageQueue.front();
            RawMessageQueue.pop();
            size = RawMessageQueue.size();
            this->lockMessageQueue.unlock();

            auto m = StupidJSON::ReadJson(std::string(message.body));
            //std::cout << std::endl<< m[PORT_S]<< std::endl ; 
            MessageQueue.push(Message(m));
        }
        
        
    }


    void Truck::Exist()
    {
        //auto lastLength = addressesOtherTrucks.size();
        auto this_length = 0;
        time_t start = time(0);
        double seconds_since_start = difftime( time(0), start);
        while (seconds_since_start < SECONDS_TO_LIVE)
        {
            HandleRawMessages();
            HandleMessages();
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            seconds_since_start = difftime( time(0), start);
        }
    

    }

    void Truck::RequestToJoin(const std::string& address, int port)
    {
        Message message;
        message._Event = Event(EventType::Joining);
        message._ReceiverPosition = LEADER_POSITION;
        message._SenderPosition = NULL_POSITION;
        message._Address=this->_myAddress;
        message._Port=this->_myPort;
        message._Body = "{\"ciao\":\"ciao\"}";
        //std::cout << address << port;
        this->Send(message, address, port);
        React(message);
        Exist();

    }
    void Truck::CreatePlatoon()
    {
        _state=TruckState::PlatoonCreation;
        Exist();
    } 



/*
LeaderElection = 97,
    LeaderElected = 98,
    Joining = 99, 
    Leaving=100, 
    Coupling=101,
    Decoupling=102,
    NewPlatoon=103,
    PlatoonNotFound=104,
    PlatoonFound =105,
    ReceivePosition=106,
    BroadcastInfo=107,
    Joined=108,
    None=109, 
    Crash=110,
    CommunicationFailure=111, 

*/

void Truck::React(const Message& message)
    {
        auto eventType = message._Event.Type();
        switch (_state)
        {
            case TruckState::Available:
                switch (eventType)
                {
                    case EventType::Joining:PRINT("I am a platoon member") _state = TruckState::PlatoonMember; break;
                    case EventType::PlatoonNotFound:_state = TruckState::PlatoonCreation; break;
                    case EventType::Leaving: _state = TruckState::Unavailable; break;
                    case EventType::None: PRINT(" None Event received") break;
                    default: break;
                }

                
                break;
            case TruckState::Elections:
               /* if(event == TruckEvent::Elected)
                {
                    _state = TruckState::Leader;
                }else if (event == TruckEvent::PositionReceived)
                {
                    _state = TruckState::SimpleMember;
                    _position-=1;
                }*/
                break;
            case TruckState::PlatoonMember:
                
                switch (eventType)
                {
                    case EventType::ReceivePosition: 
                        _position = message._ReceiverPosition;
                        _state = TruckState::SimpleMember;
                        PRINT("I am a simple member")
                    break;
                    default: std::cout << eventType; break;
                }    
                break;
            case TruckState::Leader:
                switch (eventType)
                {
                    case EventType::Joining: 
                        {
                            Message messageToSend;
                            messageToSend._Event = Event(EventType::ReceivePosition);
                            this->_platoonSize++;
                            messageToSend._ReceiverPosition = this->_platoonSize;
                            messageToSend._SenderPosition = this->_position;
                            messageToSend._Address=this->_myAddress;
                            messageToSend._Port=this->_myPort;
                            messageToSend._Body = "{\"ciao\":\"ciao\"}";

                            _Platoon[message._SenderPosition].first =message._Address;
                            _Platoon[message._SenderPosition].second = message._Port;
                            //std::cout << message._Address<< message._Port;
                            this->Send(messageToSend, message._Address, message._Port);
                            //this->BroadcastInfo();
                        }
                        break;
                    case EventType::Leaving: _state = TruckState::Unavailable; break;
                    case EventType::None: PRINT(" None Event received") break;
                    default: break;
                }

                break;
            case TruckState::SimpleMember:
                switch (eventType)
                {
                    case EventType::BroadcastInfo: 
                        {
                            //find better conversion for strings for the infos, stoi wont work here. Only works for 1 digit numbers
                            PRINT("I received the info, but i am not able to process it");
                        }
                        break;
                    case EventType::Leaving: _state = TruckState::Unavailable; break;
                    case EventType::None: PRINT(" None Event received") break;
                    default: break;
                }

                break;

            case TruckState::Unavailable:
                /* code */
                break;
            case TruckState::PlatoonCreation:
                /*if(event == TruckEvent::PlatoonCreated)
                {
                    _state = TruckState::PlatoonMember;
                }*/
                break;
            
            default:
                break;
        }
        //Update();

    }


}//end of namespace



