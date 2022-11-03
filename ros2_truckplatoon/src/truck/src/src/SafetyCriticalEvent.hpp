#ifndef SAFETYCRITICALEVENT_HPP
#define SAFETYCRITICALEVENT_HPP

#include "Event.hpp"
#include "utils/PlatoonTypes.hpp"

#include <ostream>
#include <iostream>








class SafetyCriticalEvent : protected Event
{
public:
    
    SafetyCriticalEvent(EventType Token){ _Event = Token;};
    SafetyCriticalEvent(){ _Event= EventType::None;};
    EventType Type(){return _Event;};
    
private:

};

#endif