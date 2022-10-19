#ifndef DRIVINGEVENT_HPP
#define DRIVINGEVENT_HPP

#include "Event.hpp"
#include "utils/PlatoonTypes.hpp"

class DrivingEvent : Event
{
    speedType _speed;
    stearingAngleType _stearingAngle;
    distanceType _distance;
};

#endif