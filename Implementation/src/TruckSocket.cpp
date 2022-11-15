#include "Truck.hpp"



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
        this ->myServerAddress.sin_addr.s_addr = inet_addr(myAddress.c_str());
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
        this ->myServerAddress.sin_addr.s_addr = inet_addr(myAddress.c_str());
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

    void Truck::Send(char* buffer )
    {

    }
    void Truck::Broadcast(const Message& message)
    {
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
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

    }
    
    void Truck::Send(const Message& message, int position)
    {
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        char buffer[2048];
        message.ToBuffer(buffer);
        memset(&receiver, '\0', sizeof(receiver));

        receiver.sin_family = AF_INET;
        receiver.sin_port = htons(_Platoon[position].second);
        receiver.sin_addr.s_addr = inet_addr(_Platoon[position].first.c_str());
        sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));

        close(sockfd);

    }
    void Truck::BroadcastInfo()
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
                    this->Broadcast(message);
                    _lastTimeInfo = time(0);
    }
    void Truck::Send(const Message& message, const std::string& address, int port)
    {

        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        memset(&receiver, '\0', sizeof(receiver));
        char buffer[2048];
        message.ToBuffer(buffer);
        receiver.sin_family = AF_INET;
        receiver.sin_port = htons(port);
        receiver.sin_addr.s_addr = inet_addr(address.c_str());
        sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));

        close(sockfd);

    }

    void Truck::TruckServer()
    {
        this->serverSocket=0;
        char buffer[2048];
        socklen_t addr_size;
        this->serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

        bind(this->serverSocket, (struct sockaddr*)&this ->myServerAddress, sizeof(this->myServerAddress));
        
        while(1)
        {
            struct sockaddr_in si_other;
            addr_size = sizeof(si_other);
            recvfrom(this->serverSocket, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)& si_other, &addr_size);
            printf("[+]Data Received: %s", buffer);
            
            this->lockMessageQueue.lock();
            RawMessageQueue.push(RawMessage(si_other, buffer));
            this->lockMessageQueue.unlock();

            
        }
    }

    void Truck::Update(const Message& message)
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
            Update(Message(NULL_MESSAGE));
            return;
        }
        while(size !=0)
        {

            auto message = MessageQueue.front();
            MessageQueue.pop();
            size = MessageQueue.size();
            if ( _Platoon.find(message._SenderPosition) == _Platoon.end()) {
                _Platoon[message._SenderPosition].first =message._Address;
                _Platoon[message._SenderPosition].second = message._Port;
                _platoonSize++;
            }


            HandleEvent(message._Event);
            Update(message);
            
            

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
            int count = 0;
            auto m = StupidJSON::ReadJson(std::string(message.body));
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

void Truck::HandleEvent(const Event &event)
    {
        auto eventType = event.Type();
        switch (_state)
        {
            case TruckState::Available:
                switch (eventType)
                {
                    case EventType::Joining: _state = TruckState::PlatoonMember; break;
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
                /*if(event == TruckEvent::Elected)
                {
                    _state = TruckState::Leader;
                }
                else if(event == TruckEvent::ElectNewLeader)
                {
                    _state = TruckState::Elections;
                }
                else if(event == TruckEvent::PositionReceived)
                {
                    _state = TruckState::SimpleMember;
                
                }else if(event == TruckEvent::Leave)
                {
                    _state = TruckState::Unavailable;
                }else{
                    //Error handling
                }*/
                break;
            case TruckState::Leader:
            /*
                if(event == TruckEvent::Leave)
                {
                    _state = TruckState::Unavailable;
                }else{
                    //Error handling
                }*/
                break;
            case TruckState::SimpleMember:
                /*if(event == TruckEvent::ElectNewLeader)
                {
                    _state = TruckState::Elections;
                }else if(event == TruckEvent::Leave)
                {
                    _state = TruckState::Unavailable;
                }
                if(event == TruckEvent::Elected)
                {
                    _state = TruckState::Leader;
                }
                else{
                    //Error handling
                }*/
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



