#include "Truck.hpp"


Truck::Truck()
{

    this->_id = 0;
    this->_speed = 0;
    this->_stearingAngle = 0;
    this->_distance = 0;
    this->_state = TruckState::Available;

    bool platoon = this->CheckForPlatoon();
}


Truck::Truck(u_int16_t newID):_id (newID)
{
    this->_speed = 0;
    this->_stearingAngle = 0;
    this->_distance = 0;
    this->_state = TruckState::Available;

}


bool Truck::CheckForPlatoon ()
{
    if(omp_get_num_threads() > 1)
    {
        return true;
    }
    else
    {
        return false;
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
            /* code */
            break;
        
        default:
            break;
    }

}