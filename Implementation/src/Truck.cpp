#include "Truck.hpp"


Truck::Truck()
{

    this->_id = 0;
    this->_speed = 0;
    this->_stearingAngle = 0;
    this->_distance = 0;
    this->_state = TruckState::Available;
    this ->_order = 0;

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
            WriteBus(Bus, _order, 0, EventType::PlatoonCreated);
            ReadBus(Bus);
            HandleEvent(TruckEvent::Elected);
        }
        else
        {
            //Join Platoon
        }

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

        case TruckState::PlatoonMember:
            /* code */
            break;
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
            if(event == TruckEvent::Elected){
                _state = TruckState::Leader;
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
            /* code */
            break;
        case TruckState::Leader:
            std::cout << "Truck n. " << _id << " is the leader"<<std::endl;
            break;
        case TruckState::SimpleMember:
            /* code */
            break;

        case TruckState::Unavailable:
            /* code */
            break;
        case TruckState::PlatoonCreation:
            _order = 1;
            break;
        
        default:
            break;
    }

}

void Truck::ReadBus(std::vector<Message>* Bus){
        for(auto message: *Bus)
        {
            //std::cout<< message._Event.Type() << " from: " << _id << std::endl;
        }
    };

void Truck::WriteBus(std::vector<Message>* Bus, Message *m )
{
        Bus->push_back(*m);
}

void Truck::WriteBus(std::vector<Message>* Bus,u_int16_t ID_Sender, u_int16_t ID_Receiver, Event Event)
{

        Bus->push_back(Message(ID_Sender,ID_Receiver, Event));
}