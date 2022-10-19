#ifndef SAFETYCRITICALEVENT_HPP
#define SAFETYCRITICALEVENT_HPP

#include "Event.hpp"
#include "utils/PlatoonTypes.hpp"

#include <ostream>
#include <iostream>


std::ostream& operator << ( std::ostream& outs, const SafetyEventType& p )
{
    switch (p)
    {
    case SafetyEventType::Crash:
        return outs << "Crash";
    case SafetyEventType::CommunicationFailure:
        return outs << "CommunicationFailure";
    case SafetyEventType::SafetyNone:
        return outs << "None";
    default:
        return outs << "Default";
    };
}


class SafetyCriticalEvent : Event
{
public:
    
    SafetyCriticalEvent(SafetyEventType Token):_EventType(Token){};
    SafetyCriticalEvent():_EventType(SafetyEventType::SafetyNone){};
    SafetyEventType Type(){return _EventType;};
    
private:
    SafetyEventType _EventType;

};

#endif