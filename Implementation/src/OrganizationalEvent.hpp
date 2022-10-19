#ifndef ORGANIZATIONALEVENT_HPP
#define ORGANIZATIONALEVENT_HPP

#include "Event.hpp"
#include "utils/PlatoonTypes.hpp"

#include <ostream>
#include <iostream>




std::ostream& operator << ( std::ostream& outs, const OrganizationalEventType& p )
{
    switch (p)
    {
    case OrganizationalEventType::LeaderElection:
        return outs << "LeaderElection";
    case OrganizationalEventType::Joining:
        return outs << "Joining";
    case OrganizationalEventType::Leaving:
        return outs << "Leaving";
    case OrganizationalEventType::Coupling:
        return outs << "Coupling";
    case OrganizationalEventType::Decoupling:
        return outs << "Decoupling";
    case OrganizationalEventType::OrganizationalNone:
        return outs << "None";
    default:
        return outs << "Default";
    };
}


class OrganizationalEvent : Event
{
public:
    
    OrganizationalEvent(OrganizationalEventType Token):_EventType(Token){};
    OrganizationalEvent():_EventType(OrganizationalEventType::OrganizationalNone){};
    OrganizationalEventType Type(){return _EventType;};

private:
    OrganizationalEventType _EventType;

};

#endif