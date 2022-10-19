
#ifndef PLATOONTYPES_HPP
#define PLATOONTYPES_HPP

typedef float speedType;

typedef float stearingAngleType;

typedef float distanceType;



enum OrganizationalEventType
{
    LeaderElection,
    Joining, 
    Leaving, 
    Coupling,
    Decoupling,
    OrganizationalNone
};

enum SafetyEventType
{
    Crash,
    CommunicationFailure, 
    SafetyNone
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

#endif


