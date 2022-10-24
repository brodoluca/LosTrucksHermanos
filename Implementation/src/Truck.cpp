#include "Truck.hpp"


Truck::Truck()
{

    this->_id = 0;
    this->_speed = 0;
    this->_stearingAngle = 0;
    this->_distance = 0;
    this->_state = TruckState::Available;
    this ->_position = 0;

    //bool platoon = this->CheckForPlatoon();
}


Truck::Truck(u_int16_t newID):_id (newID)
{
    this->_speed = 0;
    this->_stearingAngle = 0;
    this->_distance = 0;
    this->_state = TruckState::Available;

}


void Truck::CheckPlatoon(std::vector<Message>* Bus)
{
        int count = 0;
        for(auto message: *Bus)
        {
            count++;
        }

        if(count == 0)
        {
            HandleEvent(TruckEvent::PlatoonNotAvailable);
            WriteBus(Bus, _position, 0, EventType::PlatoonNotFound);
            //ReadBus(Bus);
            HandleEvent(TruckEvent::PlatoonCreated);
            WriteBus(Bus, _position, 0, EventType::NewPlatoon);

            HandleEvent(TruckEvent::Elected);
            WriteBus(Bus, _position, 0, EventType::LeaderElected);
        }
        else
        {
            HandleEvent(TruckEvent::Join);
            WriteBus(Bus, _position, 0, EventType::Joining, _id);
            if(!SearchFor(Bus, EventType::LeaderElected))
            {
                HandleEvent(TruckEvent::ElectNewLeader);
            }
        }

}



void Truck::HandleEvent(const TruckEvent &event)
{
    switch (_state)
    {
        case TruckState::Available:
            if (event == TruckEvent::Join)
            {
                _state = TruckState::PlatoonMember;
            }else if(event == TruckEvent::PlatoonNotAvailable)
            {
                _state = TruckState::PlatoonCreation;
            }else
            {
                //ErrorHandling
            }
            break;
        case TruckState::Elections:
            break;
        case TruckState::PlatoonMember:
            if(event == TruckEvent::Elected)
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
               
            }
        case TruckState::Leader:
            /* code */
            break;
        case TruckState::SimpleMember:
            /* code */
            break;

        case TruckState::Unavailable:
            /* code */
            break;
        case TruckState::PlatoonCreation:
            if(event == TruckEvent::PlatoonCreated)
            {
                _state = TruckState::PlatoonMember;
            }
            break;
        
        default:
            break;
    }
    Update();

}



void Truck::Update()
{
    switch (_state)
    {
        case TruckState::Available:
            break;

        case TruckState::PlatoonMember:
            for(auto message: *_Bus)
            {
                if(message._Event.Type() == EventType::ReceivePosition && message._ReceiverID == _id && _position==0){
                    auto map = StupidJSON::ReadJson(message._Body);
                    _position = std::stoi(map[NEW_POSITION]);
                    _leaderID = std::stoi(map[LEADER_ID]);
                    WriteBus(_Bus,_position, LEADER_POSITION, EventType::Joined, _id, _leaderID );
                    HandleEvent(TruckEvent::PositionReceived);
                    
                }
                    
            }
            break;
        case TruckState::Leader:
            if(!_isLeader){
                _isLeader = true;
                return;
            }
        
                for(auto message = _Bus->end(); (*message)._Event.Type() != EventType::LeaderElected; message--)
                {
                    if((*message)._Event.Type() == EventType::LeaderElected)
                        break;
                    //if((*message)._SenderPosition != 1)
                      //  _Bus->erase(message);
                    if((*message)._Event.Type() == EventType::Joining)
                    {
                        _platoonSize +=1;
                        Message newMessage( _position, 0, EventType::ReceivePosition, _id, (*message)._SenderID);
                        std::string  Tags[] = {NEW_POSITION, LEADER_ID};
                        std::string Values[] = {std::to_string(int(_platoonSize)), std::to_string(int(_id))};
                        newMessage._Body = StupidJSON::CreateJsonFromTags(Tags, Values, 2);
                        
                        
                        WriteBus(_Bus,&newMessage);

                        // Write on the bus the new member position
                        //Each message will have a body in json for the content
                        // Grande giuseppe per l'idea
                    }
                }
                

            
            break;
        case TruckState::SimpleMember:
             
            break;

        case TruckState::Unavailable:
            /* code */
            break;
        case TruckState::PlatoonCreation:
            _position = LEADER_POSITION;
            _platoonSize = 1;
            
            break;
        case TruckState::Elections:
            break;
        default:
            break;
    }
    std::cout << "Truck n. " << _id << " : " << _state <<std::endl;

}









Message Truck::PopBackLastMessage(std::vector<Message>* Bus)
{
    return Bus->back();
}


void Truck::ReadBus(std::vector<Message>* Bus){
        for(auto message: *Bus)
        {
            //std::cout<< message._Event.Type() << " from: " << _id << std::endl;
        }
};


bool Truck::SearchFor(std::vector<Message>* Bus, const EventType& Event)
{
    for(auto message: *Bus)
        {
            if(message._Event.Type() == Event)
                return true;
        }
    return false;
}


void Truck::WriteBus(std::vector<Message>* Bus, Message *m )
{
        Bus->push_back(*m);
}

//void Truck::WriteBus(std::vector<Message>* Bus,u_int16_t SenderPosition, u_int16_t ReceiverPosition, Event Event)
//{

  //      Bus->push_back(Message(SenderPosition,ReceiverPosition, Event));
//}

void Truck::WriteBus(std::vector<Message>* Bus,u_int16_t SenderPosition, u_int16_t ReceiverPosition, Event Event, int16_t SenderID, int16_t ReceiverID)
{
    Bus->push_back(Message(SenderPosition,ReceiverPosition, Event, SenderID, ReceiverID));
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


void Truck::SetBus(std::vector<Message>* Bus){
    _Bus = Bus;
}