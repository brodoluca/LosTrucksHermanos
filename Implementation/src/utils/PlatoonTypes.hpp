
#ifndef PLATOONTYPES_HPP
#define PLATOONTYPES_HPP

#include "include.hpp"

typedef float speedType;

typedef float stearingAngleType;

typedef float distanceType;





enum  EventType
{
    LeaderElection,
    Joining, 
    Leaving, 
    Coupling,
    Decoupling,
    PlatoonCreated,
    None, 

    Crash,
    CommunicationFailure, 
};


static std::ostream& operator << ( std::ostream& outs, const EventType& p )
{
    switch (p)
    {
    case EventType::Crash:
        return outs << "Crash";
    case EventType::CommunicationFailure:
        return outs << "CommunicationFailure";
    case EventType::LeaderElection:
        return outs << "LeaderElection";
    case EventType::Joining:
        return outs << "Joining";
    case EventType::Leaving:
        return outs << "Leaving";
    case EventType::Coupling:
        return outs << "Coupling";
    case EventType::Decoupling:
        return outs << "Decoupling";
    case EventType::PlatoonCreated:
        return outs << "PlatoonCreated";   
    case EventType::None:
        return outs << "None";
    default:
        return outs << "No State";
    };
};

enum TruckState
{
    Available, 
    PlatoonMember, 
    Leader, 
    SimpleMember, 
    Unavailable, 
    PlatoonCreation
};


enum TruckEvent
{
    Join, 
    Elected, 
    NotElected, 
    Failure, 
    Fixed, 
    NotFixed, 
    PlatoonNotAvailable, 
    Leave 
};
class Event
{
public:
    Event() {};
    Event(EventType Token){_Event = Token;};
    EventType Type(){return _Event;};
protected:
    EventType _Event;

};

struct Message
{
            Message(u_int16_t ID_Sender, u_int16_t ID_Receiver, Event Event): _ID_Sender(ID_Sender), _ID_Receiver(ID_Receiver), _Event(Event){};
            u_int16_t _ID_Sender;
            u_int16_t _ID_Receiver;
            Event _Event;

};


#endif




