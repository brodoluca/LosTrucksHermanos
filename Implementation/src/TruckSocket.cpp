#include "Truck.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cmath>



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
        distanceSensor = new std::thread([this]() {ReadDistanceSencor();});
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
        distanceSensor = new std::thread([this]() {ReadDistanceSencor();});
        

    }


///
/// Setters and Getters
///
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

/*
 Functions responsible for the communication
 */


///@brief broadcasts the message to all the trucks in the platoon
///@par[input] Message to broadcast
///@return True if successfull, False if it's unsuccessfull
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
        auto truck = _Platoon.begin();
        truck++;
        for(; truck != _Platoon.end(); ++truck)
        {
            
            receiver.sin_port = htons(truck->second.second);
            receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
            sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        }

//        printf("[+]Data Send: %s\n", buffer);
        

        close(sockfd);
        return true;

    }
///@brief Sends a message to a truck in a specific position
///@par[message] Message to send
///@par[position] position of the truck
///@return True if successfull, False if it's unsuccessfull

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

///@brief Creates a message containing all the informations and broadcasts it to every truck
///@return True if successfull, False if it's unsuccessfull

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
                //std::cout << message._Body<<std::endl;

                    _lastTimeInfoSent = time(0);
                    return check;
    }

///@brief Sends a message to a truck with a specific address and port
///@par[message] Message to send
///@par[address] address of the truck
///@par[port] port of the truck
///@return True if successfull, False if it's unsuccessfull

    bool Truck::Send(const Message& message, const std::string& address, int port)
    {

        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        if(sockfd <0)
            return false;


        //char broadcast = '1';
        memset(&receiver, '\0', sizeof(receiver));
        char buffer[2048];
        message.ToBuffer(buffer);
        receiver.sin_family = AF_INET;
        receiver.sin_port = htons(port);
        receiver.sin_addr.s_addr = inet_addr(address.c_str());
        auto a = sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));

        //std::cout << a;
        close(sockfd);
        return true;

    }

///@brief Sends information to the interface
///@par[InterfaceAddress] address of the interface
///@par[InterfacePort] port of the interface
///@return True if successfull, False if it's unsuccessfull

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


///@brief Creates a server thanks to which the trucks are able to receive messages
///        it  puts the messages in a queue containing Raw Messages (aka the strings received through the sockets)
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
        
        
        bind(serverSocket, (struct sockaddr*)&this->myServerAddress, sizeof(myServerAddress));
        //std::cout << a<<std::endl;
        while(1)
        {
            struct sockaddr_in si_other;
            addr_size = sizeof(si_other);
            ssize_t a = recvfrom(serverSocket, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)& si_other, &addr_size);
            //if(a <0)
              //  std::cout << a;
            //if(DEBUG_MODE){
              //  printf("[+]Data Received: %s", buffer);
                //printf("[+]Time %ld", time(0));
            //}
            
            this->lockMessageQueue.lock();
            RawMessageQueue.push(RawMessage(si_other, buffer));
            this->lockMessageQueue.unlock();
            
        }
    }

///@brief Utility function to send to the leader that the truck is alive
    bool Truck::SendAlive()
    {
        Message message;
        message._Event = Event(EventType::IamAlive);
        message._ReceiverPosition = LEADER_POSITION;
        message._SenderPosition = _position;
        message._Address=this->_myAddress;
        message._Port=this->_myPort;
        message._Body = "{\"I am\":\"alive\"}";
        
        return Send(message, _Platoon[LEADER_POSITION].first, _Platoon[LEADER_POSITION].second);
    }

///@brief Main loop of the truck behaviour. When called, the truck will do something depending on the state it finds himself in.
    void Truck::Update()
    {
        HandleRawMessages();
        HandleMessages();
        switch (_state)
            {
            case TruckState::Available:
                
                break;

            case TruckState::PlatoonMember:
                break;
                    
            case TruckState::Leader:
                if(!_isLeader){
                    _position = 1;
                    _isLeader = true;
                    _speed = 100;
                    BroadcastInfo();
                    return;
                }
                if(difftime( time(0), _lastTimeInfoSent) > SECONDS_TO_INFO)
                {
                    BroadcastInfo();
                }
                CheckAliveTime();
                //if null message
                //broadcast info
                break;
            case TruckState::SimpleMember:
                    if(difftime( time(0), _lastMessageAliveSent) > SECONDS_TO_SEND_ALIVE)
                    {
                        
                            SendAlive();
                        _lastMessageAliveSent = time(0);
                    }
                    CheckAliveTime();
                break;

            case TruckState::Unavailable:
                /* code */
                break;
            case TruckState::PlatoonCreation:
                _position = LEADER_POSITION;
                _platoonSize = 1;
                PRINT(" I am the new leader");
                _state = Leader;
                _Platoon[LEADER_POSITION].first =_myAddress;
                _Platoon[LEADER_POSITION].second = _myPort;
                break;
            case TruckState::Elections:
                    if(_countElection >= _platoonSize){
                        if(_position == NEW_LEADER_POSITION)
                        {
                            _state = TruckState::Leader;
                            _position = LEADER_POSITION;
                            
                            for(auto & [position, second]:_Platoon)
                                _PlatoonAliveTime[position-1] = time(0);
                            std::cout << "I am the leader" <<std::endl;
                        }else{
                            _state = TruckState::SimpleMember;
                            _position--;
                        }
                        _Platoon.erase(1);
                        
                        {
                            //let's rebuild the map
                            auto temp = _Platoon;
                            _Platoon.clear();
                            int count = 1;
                            for(auto & [position, second]:temp)
                            {
                                _Platoon[count] = second;
                                count++;
                            }
                            
                        }
                        _countElection=0;
                    }
                    
                

            default:
                break;
        }
        
    }


///@brief Pops a message from the queue and calls the react function. In case there are no messages, it will call the update function directly.

    void Truck::HandleMessages()
    {
        auto size = MessageQueue.size();
        if(size == 0)
        {
            //Update();
            return;
        }
        while(size >0)
        {
            
            auto message = MessageQueue.front();
            MessageQueue.pop();
            size = MessageQueue.size();
            
            std::cout << message._Address << " "<<message._Port << " "<<message._Event.Type() <<std::endl;
           
            // << std::endl<< message._Port<< std::endl ;
            React(message);
            //Update();
            
            

        }
    }

///@brief Pops a message from the queue contianing the Raw Messages and pushes it into the main one
///The distinction between RawMessages and normal messages exists so that we do not waste time in the server to convert the Json string into Message struct.
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

///@brief Just for debug purposes, it basically prints the platoon
    void Truck::DebugInfo()
    {
        std::cout << "The platoon is composed of:" <<std::endl;
        for(auto iter = _Platoon.begin(); iter != _Platoon.end(); ++iter)
            {
                std::cout << "Truck in position : " << iter->first << " with address " << iter->second.first << ":" <<iter->second.second << std::endl;
            //ignore value
            //Value v = iter->second;
            }
    }
///@brief Main Loop for the truck
///Only the Handle Messages functions are called.
///Potentially we can simplify it by putting the Handlemessages() into the update function and only call that (also removing the HandleRawMessages, see discussion above)
    void Truck::Exist()
    {
        //auto lastLength = addressesOtherTrucks.size();
        //auto this_length = 0;
        time_t start = time(0);
        double seconds_since_start = difftime( time(0), start);
        double time_to_print = time(0);
        while (seconds_since_start < SECONDS_TO_LIVE)
        {
            this->Update();
            if(DEBUG_MODE)
                if(difftime( time(0), time_to_print) > 4 ){
                    DebugInfo();
                    time_to_print = time(0);
                }
                
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            seconds_since_start = difftime( time(0), start);
            
            
        }
    

    }
    
///@brief Truck requests a leader with address and port to join the platoon
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


///@brief The leader calls this function to mofigy the platoon position in case of a dead truck
void Truck::UpdatePlatoonPosition( int leavingTruck)
{
//    so we dont waste time instantiating the message and so on
//    if(_platoonSize<=2) return;
    
    Message messageToSend;
    messageToSend._Event = Event(EventType::ReceivePosition);
    
    
    
    //messageToSend._ReceiverPosition = this->_platoonSize;
    //messageToSend._SenderPosition = this->_position;
    messageToSend._Address=this->_myAddress;
    messageToSend._Port=this->_myPort;
    messageToSend._Body = "{\"TRUCK_DEAD\":\"" + std::to_string(leavingTruck)+"\"}";
    messageToSend._SenderPosition = this->_position;
    struct sockaddr_in receiver;
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    if(sockfd <0)
        return ;
    char buffer[2048];
   
    memset(&receiver, '\0', sizeof(receiver));
    receiver.sin_family = AF_INET;
    auto truck = _Platoon.begin();
    if(!(leavingTruck >= _Platoon.size())){
        std::advance(truck,leavingTruck);
        for(; truck != _Platoon.end(); ++truck)
        {
            messageToSend._ReceiverPosition = truck->first -1;
            messageToSend.ToBuffer(buffer);
            receiver.sin_port = htons(truck->second.second);
            receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
            sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        }
    }
        
    truck = _Platoon.begin();
    std::advance(truck,leavingTruck-1);
    messageToSend._Event = Event(EventType::TruckDead);
    for(; truck != _Platoon.begin(); --truck)
    {
        
        messageToSend._ReceiverPosition = truck->first;;
        messageToSend.ToBuffer(buffer);
        receiver.sin_port = htons(truck->second.second);
        receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
        sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
    }
    
        
    

//       Let's test this with the GUI
//    It's basically sending the message to the GUI
    /*
    messageToSend._ReceiverPosition = NULL_POSITION;
    messageToSend.ToBuffer(buffer);
    receiver.sin_port = htons(GUI_PORT);
    receiver.sin_addr.s_addr = inet_addr(GUI_ADDRESS);
    sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
     */
    close(sockfd);
}


void Truck ::CheckAliveTime()
{
    if(this->isLeader()){
        if(_platoonSize >2)
        {
            // We check which truck are dead
            std::vector<int> positions_to_remove;
            for(auto & [position, AliveTime]:_PlatoonAliveTime)
            {
                if(difftime(time(0),AliveTime)> SECONDS_TO_BE_ALIVE)
                    positions_to_remove.push_back(position);
                
            }
            for(int position:positions_to_remove){
                _platoonSize-=1;
                RemoveTruck(position);
                
            }
            
            //let's rebuild the map
            auto temp = _Platoon;
            _Platoon.clear();
            int count = 1;
            for(auto & [position, second]:temp)
            {
                _Platoon[count] = second;
                count++;
            }
            
            
            auto temp_alive = _PlatoonAliveTime;
            _PlatoonAliveTime.clear();
            count = 2;
            for(auto & [position, second]:temp_alive)
            {
                _PlatoonAliveTime[count] = second;
                count++;
            }
            
            /*
             As the truck dies, we need to find a way to replace the key in the map with the correct position
             */
        }
        else if(_platoonSize >1)
        {
            
            // since we are the leader, the truck who dies is automatically in position 2
            if(difftime(time(0),_PlatoonAliveTime[2]) > SECONDS_TO_BE_ALIVE){
                //std::cout << difftime(time(0),_PlatoonAliveTime[2])<<std::endl;
                RemoveTruck(2);
                _platoonSize--;
            }
        }
    }else{
        if(_platoonSize>=2 )
            if(difftime(time(0),_lastInfoReceived) > SECONDS_TO_BE_ALIVE){
                if(_platoonSize >2)
                    BroadcastLeaderDead();
                else{
                    Message messageToSend;
                    messageToSend._Event = Event(EventType::LeaderElection);
                    messageToSend._Address=this->_myAddress;
                    messageToSend._ReceiverPosition=BROADCAST;
                    messageToSend._Port=this->_myPort;
                    messageToSend._Body = "{\"TRUCK_DEAD\":\"1\"}";
                    messageToSend._SenderPosition = this->_position;
                    
                    Send(messageToSend, _myAddress,_myPort);
                    
                }
                _countElection = 1;
                _platoonSize--;
            }
    }
//    }else if(_platoonSize>2){
//        if(difftime(time(0),_lastMessageSent) > SECONDS_TO_BE_ALIVE){
//            BroadcastLeaderDead();
//        }
            //leader is dead
            //we need to elections
    
    
}

void Truck::React(const Message& message)
    {
        auto eventType = message._Event.Type();
    
        if(eventType == EventType::IamAlive)
        {
            //std::cout << "I am here" << std::endl;
            _PlatoonAliveTime[message._SenderPosition] = time(0);
            return;
        }
        
        switch (_state)
        {
            case TruckState::Available:
                switch (eventType)
                {
                    case EventType::Joining:
                        PRINT("I am a platoon member")
                        _state = TruckState::PlatoonMember;
                        break;
                    case EventType::PlatoonNotFound:
                        _state = TruckState::PlatoonCreation;
                        break;
                    case EventType::Leaving:
                        _state = TruckState::Unavailable;
                        break;
                    case EventType::None:
                        PRINT(" None Event received")
                        break;
                    
                    default:
                        PRINT(" Whats'up?") break;
                        break;
                }
                break;
            case TruckState::Elections:
                
                if(eventType == EventType::LeaderElection)
                {
                    _countElection++;
                }
                std::cout << "i am in the election state" <<std::endl;;
                break;
            case TruckState::PlatoonMember:
                
                switch (eventType)
                {
                    case EventType::AddAllTrucks:
                    {
                        auto mBody = StupidJSON::ReadJson(message._Body);
//                        std::cout <<message._Body;
                        int positionToAdd = 2;
                        auto truckInfo = mBody.begin();
                        //truckInfo++;
                        while (truckInfo!=mBody.end()) {
                            try {
                                _Platoon[positionToAdd] = std::pair<std::string,int>(truckInfo->second, std::stoi(truckInfo->first));
                            } catch (const std::exception& e) {
                                std::cout << "Caught exception \"" << e.what() << "\"\n";
                                _Platoon[positionToAdd] = std::pair<std::string,int>(truckInfo->second,90909);
                                Message messageToSend;
                                messageToSend._Event = Event(EventType::IsTruckCorrect);
                                messageToSend._Address=this->_myAddress;
                                messageToSend._ReceiverPosition=LEADER_POSITION;
                                messageToSend._Port=this->_myPort;
                                messageToSend._Body = "{\"PC\":\""+std::to_string(positionToAdd)+"\"}";
                                messageToSend._SenderPosition = this->_position;
                                Send(message, message._Address, message._Port);
                            }
                            
                            truckInfo++;
                            positionToAdd++;
                        }
                        break;
                    }
                    case EventType::ReceivePosition:
                        _position = message._ReceiverPosition;
                        _state = TruckState::SimpleMember;
                        
                        
                        _Platoon[LEADER_POSITION].first =message._Address;
                        _Platoon[LEADER_POSITION].second = message._Port;
                        
                        _Platoon[_position].first =_myAddress;
                        _Platoon[_position].second = _myPort;
                        PRINT("I am a simple member")
                        _platoonSize=_position;
                        SendAlive();
                        _lastInfoReceived=time(0);
                        //_lastAliveSent = time(0);
                    break;
                    default:
                        Message messageToSend;
                        messageToSend._Event = Event(EventType::needPosition);
                        messageToSend._ReceiverPosition = LEADER_POSITION;
                        messageToSend._SenderPosition = this->_position;
                        messageToSend._Address=this->_myAddress;
                        messageToSend._Port=this->_myPort;
                        messageToSend._Body = "{\"GIMME POSITION\":\"GIMME POSITIon\"}";
                        _Platoon[LEADER_POSITION].first =message._Address;
                        _Platoon[LEADER_POSITION].second = message._Port;
                        Send(messageToSend, message._Address, message._Port);
                        break;
                }
                break;
            case TruckState::Leader:
                switch (eventType)
                {
                    case EventType::Joining:
                        {
                            if (this->CheckIfTruckExists(message._Address, message._Port)) return;
                            this->_platoonSize++;
                            Message messageToSend;
                            messageToSend._Event = Event(EventType::ReceivePosition);

                            messageToSend._ReceiverPosition = this->_platoonSize;
                            messageToSend._SenderPosition = this->_position;
                            messageToSend._Address=this->_myAddress;
                            messageToSend._Port=this->_myPort;
                            messageToSend._Body = "{\"ciao\":\"ciao\"}";
                            //std::cout << message._Address<< message._Port;
                            this->Send(messageToSend, message._Address, message._Port);
                            //this->BroadcastInfo();
                            
                            /*
                             WE NEED TO TELL EVERYBODY THAT THERE'S A NEW TRUCK AS WELL
                             */
                            
                                
                            _Platoon[this->_platoonSize].first =message._Address;
                            _Platoon[this->_platoonSize].second = message._Port;
                            _PlatoonAliveTime[this->_platoonSize] = time(0);
                            if (_platoonSize >2){
                                BroadcastNewPlatoonMember();
                                SharePlatoonMembers(_platoonSize);
                            }
                            
                            
                            
                            
                        }
                        break;
                    case EventType::needPosition:
                        {
                            
                            Message messageToSend;
                            messageToSend._Event = Event(EventType::ReceivePosition);
                            messageToSend._ReceiverPosition = this->_platoonSize;
                            messageToSend._SenderPosition = this->_position;
                            messageToSend._Address=this->_myAddress;
                            messageToSend._Port=this->_myPort;
                            messageToSend._Body = "{\"ciao\":\"ciao\"}";

                            _Platoon[this->_platoonSize].first =message._Address;
                            _Platoon[this->_platoonSize].second = message._Port;
                            _PlatoonAliveTime[this->_platoonSize] = time(0);
                            //std::cout << message._Address<< message._Port;
                            this->Send(messageToSend, message._Address, message._Port);
                            //this->BroadcastInfo();

                            
                            
                        }
                    break;
                    case EventType::Leaving:
                        _platoonSize-=1;
                        _Platoon.erase(message._SenderPosition);
                        
                        UpdatePlatoonPosition(message._SenderPosition);
                        
                        break;
                    case EventType::None: PRINT(" None Event received") break;
                    case EventType::IamAlive:
                        _PlatoonAliveTime[message._SenderPosition] =  time(0);
                        break;
                        
                    case EventType::TruckDead:
                    {
                        RemoveTruck(message._SenderPosition);
                        //Handle truck dead
                        //Ping and wait 1 sec
                        //if not back
                        //basically, check which truck is dead and reassign positions to trucks after it
                        //create a different fnction for it
                    }
                        break;
                    case EventType::IsTruckCorrect:
                        std::cout<< "OOPS";
                        SharePlatoonMembers(message._SenderPosition);
                        break;
                    default: break;
                }

                break;
            case TruckState::SimpleMember:
                switch (eventType)
                {
                    case EventType::BroadcastInfo:
                        {
                            _lastInfoReceived = time(0);
                            auto Info = StupidJSON::ReadJson(message._Body);
                            try {
                                _platoonSize = std::stoi(Info["PlatoonSize"]);
                            } catch (...) {
                                
                            }
                           
                            //find better conversion for strings for the infos, stoi wont work here. Only works for 1 digit numbers
                            //PRINT("I received the info, but i am not able to process it");
                        }
                        break;
                    case EventType::ReceivePosition:
                        {
                            auto it = _Platoon.find(_position);
                            if (it != _Platoon.end())
                            {
                                _Platoon.erase(_position);
                                
                            }
                            
                        }
                        _position = message._ReceiverPosition;
                        _Platoon[_position].first =_myAddress;
                        _Platoon[_position].second = _myPort;
                        //_platoonSize--;
                        PRINT("I received my new position");
                        
                        
                        
                        break;
                    case EventType::Leaving: _state = TruckState::Unavailable; break;
                    case EventType::TruckDead:
                    {
                        
                        auto mBody = StupidJSON::ReadJson(message._Body);
                        //TRY HERE
                        _Platoon.erase(_Platoon.find(std::stoi(mBody["TRUCK_DEAD"])));
                    }
                        break;
                    case EventType::AddNewMember:
                    {
                        
                        auto mBody = StupidJSON::ReadJson(message._Body);
                        _platoonSize++;
                        
                        //_platoonSize = std::stoi(mBody[PLATOON_SIZE].c_str());
                        //YOU SHOULD RECEIVE THE NEW PLATOON SIZE AS WELL
                        _Platoon[_platoonSize].first = mBody[ADDRESS_S];
                        
                        try {
                            _Platoon[_platoonSize].second = std::stoi(mBody[PORT_S]);
                        } catch (...) {
                            _Platoon[_platoonSize].second = 1234;
                        }
                        
                    }
                        break;
                    case EventType::LeaderElection:
                        _state = TruckState::Elections;
                        break;
                    case EventType::AddAllTrucks:
                    {
                        auto mBody = StupidJSON::ReadJson(message._Body);
                        //std::cout <<message._Body;
                        int positionToAdd = 2;
                        auto truckInfo = mBody.begin();
                        //truckInfo++;
                        while (positionToAdd < _position && truckInfo!=mBody.end()) {
                            try {
                                _Platoon[positionToAdd] = std::pair<std::string,int>(truckInfo->second, std::stoi(truckInfo->first));
                            } catch (...) {
                                _Platoon[positionToAdd] = std::pair<std::string,int>(truckInfo->second,90909);

                                Message messageToSend;
                                messageToSend._Event = Event(EventType::IsTruckCorrect);
                                messageToSend._Address=this->_myAddress;
                                messageToSend._ReceiverPosition=LEADER_POSITION;
                                messageToSend._Port=this->_myPort;
                                messageToSend._Body = "{\"PC\":\""+std::to_string(positionToAdd)+"\"}";
                                messageToSend._SenderPosition = this->_position;
                                Send(message, message._Address, message._Port);
                                std::cout << "HEX"<<std::endl;
                            }

                            truckInfo++;
                            positionToAdd++;
                        }
                    }
                        break;
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

    void Truck::RemoveTruck(int position)
    {
        if(this->isLeader())
        {
            auto it = _Platoon.find(position);
            if (it != _Platoon.end())
            {
                
                try {
                    _Platoon.erase(position);
                    _PlatoonAliveTime.erase(position);
                    UpdatePlatoonPosition(position);
                } catch (...) {
                    std::cout<<"Ooops\n";
                }
                
                
            }
        }
        else
        {
            //send to leader
        }
        
        
    }


    void Truck::RemoveTruck(std::vector<int> positions)
    {
        for(int position : positions)
            RemoveTruck(position);
        
    }

    void Truck::BroadcastNewPlatoonMember()
    {
        
        Message messageToSend;
        messageToSend._Event = Event(EventType::AddNewMember);
        messageToSend._ReceiverPosition = BROADCAST;
        messageToSend._SenderPosition = this->_position;
        messageToSend._Address=this->_myAddress;
        messageToSend._Port=this->_myPort;
        std::string  Tags[] = { PORT_S,ADDRESS_S,PLATOON_SIZE };
        std::string Values[] = {std::to_string(_Platoon[this->_platoonSize].second),_Platoon[this->_platoonSize].first,  std::to_string(_platoonSize) };

        messageToSend._Body = StupidJSON::CreateJsonFromTags(Tags, Values, 3);
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

        if(sockfd <0)
            return;
        char buffer[2048];
        messageToSend.ToBuffer(buffer);
        memset(&receiver, '\0', sizeof(receiver));
        receiver.sin_family = AF_INET;
        auto truck = _Platoon.begin();
        truck++;
        for(; truck != --_Platoon.end(); ++truck)
        {
            
            receiver.sin_port = htons(truck->second.second);
            receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
            sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        }


        close(sockfd);

    }

    void Truck::ReadDistanceSencor() {
        while (1) {
            
            std::this_thread::sleep_for(std::chrono::milliseconds(READ_FREQUENCY));
            if (!this->isLeader()) {
                srand((unsigned) time(NULL));
                int a =160- (rand() % 10);
                sensorReads.push( a);
                if (DEBUG_MODE)
                    std::cout << "last read: " <<a<< std::endl;
                if (a <= 150) {
//                    trigger distance event
                    SlowDown(a);
                }else if (a >= 160){
                    SpeedUp(a);
                    //go faster
                    //random 50 50 to decide if its my maximum
                    //send to leader hey slow down for 10 s
                    //leader slows down.
            }
                
            }
            

            
        };
    }

    void Truck::SharePlatoonMembers(int position) {
        Message messageToSend;
        messageToSend._Event = Event(EventType::AddAllTrucks);
        messageToSend._ReceiverPosition = _platoonSize;
        messageToSend._SenderPosition = this->_position;
        messageToSend._Address=this->_myAddress;
        messageToSend._Port=this->_myPort;
        
        
        //we dont count the leader and the truck who just joined
        std::string  addresses[_platoonSize-2] ;
        std::string ports[_platoonSize-2];
        for(int c = 2; c < _platoonSize;c++)
        {
            addresses[c-2] = _Platoon[c].first;
            ports[c-2] =  std::to_string(_Platoon[c].second);
            //std::cout << _Platoon[c].first;;
        }
        
        //for(auto a :addresses)
          //  std::cout << a;
        
        
        messageToSend._Body = StupidJSON::CreateJsonFromTags( ports, addresses,_platoonSize-2);
        Send(messageToSend, position);
        
    }

    void Truck::SlowDown(int distance) {
//        Print using the macro that the truck is slowing down;
//        calculate for how much time (define a way based on the distance)
        //send a meesage with the event slowdown to all the trucks behind me
        
        PRINT("I am slowing down");
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        char buffer[2048];
        Message messageToSend;
        messageToSend._Event = Event(EventType::SlowDown);
        messageToSend._Address=this->_myAddress;
        messageToSend._ReceiverPosition=BROADCAST;
        messageToSend._Port=this->_myPort;
        messageToSend._Body = "{\"Time\":\"1\"}";
        messageToSend._SenderPosition = this->_position;
        messageToSend.ToBuffer(buffer);
        memset(&receiver, '\0', sizeof(receiver));
        receiver.sin_family = AF_INET;
        auto truck = _Platoon.find(_position);
        for(; truck != _Platoon.end(); ++truck)
        {
            receiver.sin_port = htons(truck->second.second);
            receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
            sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        }
        
        
    }

    void Truck::SpeedUp(int distance) {
        
        PRINT("I am speeding up");
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        char buffer[2048];
        Message messageToSend;
        messageToSend._Event = Event(EventType::SlowDown);
        messageToSend._Address=this->_myAddress;
        messageToSend._ReceiverPosition=BROADCAST;
        messageToSend._Port=this->_myPort;
        messageToSend._Body = "{\"Time\":\"1\"}";
        messageToSend._SenderPosition = this->_position;
        messageToSend.ToBuffer(buffer);
        memset(&receiver, '\0', sizeof(receiver));
        receiver.sin_family = AF_INET;
        auto truck = _Platoon.find(_position);
        for(; truck != _Platoon.end(); ++truck)
        {
            receiver.sin_port = htons(truck->second.second);
            receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
            sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        }
    }

    bool Truck::BroadcastLeaderDead() {
        struct sockaddr_in receiver;
        int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

        if(sockfd <0)
            return false;
        char buffer[2048];
        Message messageToSend;
        messageToSend._Event = Event(EventType::LeaderElection);
        messageToSend._Address=this->_myAddress;
        messageToSend._ReceiverPosition=BROADCAST;
        messageToSend._Port=this->_myPort;
        messageToSend._Body = "{\"TRUCK_DEAD\":\"1\"}";
        messageToSend._SenderPosition = this->_position;
        messageToSend.ToBuffer(buffer);
        memset(&receiver, '\0', sizeof(receiver));
        receiver.sin_family = AF_INET;
        auto truck = _Platoon.begin();
        truck++;
        for(; truck != _Platoon.end(); ++truck)
        {
            receiver.sin_port = htons(truck->second.second);
            receiver.sin_addr.s_addr = inet_addr(truck->second.first.c_str());
            sendto(sockfd, buffer, size_t(BUFFER_SIZE), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        }

//        printf("[+]Data Send: %s\n", buffer);
        

        close(sockfd);
        return true;;
    }



bool Truck::CheckIfTruckExists(const std::string& address, int port)
{
    if(_platoonSize <2) return false;
    for (auto &[truck, info] : _Platoon)
    {
        if (info.first == address && info.second ==port) {
            return true;
        }
    }
    return false;
}



}//end of namespace



