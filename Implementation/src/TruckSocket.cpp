#include "Truck.hpp"



namespace TruckSocket
{

    Truck::~Truck()
    {
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
        //bool platoon = this->CheckForPlatoon();
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
            //this->lockAddresses.lock();
            for(auto address : addressesOtherTrucks){
                 if(address.sin_addr.s_addr == message.sender.sin_addr.s_addr){
                    count++;
                    break;
                }
            }
            if(count == 0 )
                addressesOtherTrucks.push_back(message.sender);

            count = 0;
            
            //    this->lockAddresses.unlock();
        }
        
        
    }


    void Truck::Exist()
    {
        auto lastLength = addressesOtherTrucks.size();
        auto this_length = 0;
        while (1)
        {
            HandleRawMessages();
            HandleMessages();
            //std::this_thread::sleep_for(std::chrono::seconds(1));
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



