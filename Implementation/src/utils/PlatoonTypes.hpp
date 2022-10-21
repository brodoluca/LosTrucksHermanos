
#ifndef PLATOONTYPES_HPP
#define PLATOONTYPES_HPP

#include "include.hpp"

typedef float speedType;

typedef float stearingAngleType;

typedef float distanceType;



// Type of the events that could happen during the interaction between trucks in the platoon
enum  EventType
{
    LeaderElection,
    LeaderElected,
    Joining, 
    Leaving, 
    Coupling,
    Decoupling,
    NewPlatoon,
    PlatoonNotFound,
    PlatoonFound,
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
    case EventType::NewPlatoon:
        return outs << "NewPlatoon";   
    case EventType::PlatoonNotFound:
        return outs << "PlatoonNotFound";
    case EventType::LeaderElected:
        return outs << "LeaderElected";
    case EventType::PlatoonFound:
        return outs << "PlatoonFound";
    case EventType::None:
        return outs << "None";
    default:
        return outs << "No State";
    };
};



//States a truck could be in
enum TruckState
{
    Available, 
    PlatoonMember, 
    Leader, 
    SimpleMember, 
    Unavailable, 
    PlatoonCreation, 
    Elections
};



static std::ostream& operator << ( std::ostream& outs, const TruckState& p )
{
    switch (p)
    {
    case TruckState::Available:
        return outs << "Available";
    case TruckState::PlatoonMember:
        return outs << "PlatoonMember";
    case TruckState::Leader:
        return outs << "Leader";
    case TruckState::SimpleMember:
        return outs << "SimpleMember";
    case TruckState::Unavailable:
        return outs << "Unavailable";
    case TruckState::PlatoonCreation:
        return outs << "PlatoonCreation";
    case TruckState::Elections:
        return outs << "Elections";
    default:
        return outs << "No State";
    };
};


//Events that are internal of any truck. Different from the events above. Those are the transitions of the state machine, 
// Different things
enum TruckEvent
{
    Join, 
    Elected, 
    NotElected, 
    Failure, 
    Fixed, 
    NotFixed, 
    PlatoonNotAvailable, 
    Leave, 
    PlatoonCreated, 
    ElectNewLeader
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
            Message(u_int16_t SenderPosition, u_int16_t ReceiverPosition, Event Event,u_int16_t SenderID = -1, u_int16_t ReceiverID = -1)
            : _SenderPosition(SenderPosition), _ReceiverPosition(ReceiverPosition), _Event(Event), _SenderID(SenderID),  _ReceiverID(ReceiverID)
            {};
            u_int16_t _SenderPosition;
            u_int16_t _ReceiverPosition;
            Event _Event;
            int16_t _SenderID;
            int16_t _ReceiverID;

};


#endif




