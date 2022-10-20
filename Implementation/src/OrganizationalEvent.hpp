#ifndef ORGANIZATIONALEVENT_HPP
#define ORGANIZATIONALEVENT_HPP

#include "Event.hpp"
#include "utils/PlatoonTypes.hpp"

#include <ostream>
#include <iostream>







class OrganizationalEvent : protected Event
{
public:
    
    OrganizationalEvent(EventType Token){ _Event = Token;};
    OrganizationalEvent(){ _Event = EventType::None;};
    EventType Type(){return _Event;};

private:

};

#endif