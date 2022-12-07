
#ifndef PLATOONTYPES_HPP
#define PLATOONTYPES_HPP

#include "include.hpp"

#define SECONDS_TO_LIVE 99999
#define SECONDS_TO_INFO 2

#define SECONDS_TO_SEND_ALIVE 3
#define SECONDS_TO_BE_ALIVE 10

#define NEW_POSITION "NewPosition"
#define LEADER_ID "LeaderID"
#define PLATOON_SIZE "PlatoonSize"
#define SPEED "Speed"
#define SAFETY_DISTANCE "SafetyDistance"
#define PLATOON_SIZE "PlatoonSize"


#define GUI_ADDRESS "172.20.10.5"
#define GUI_PORT 9876


#define NULL_MESSAGE false

#define SENDER_POSITION 'S'
#define RECEIVER_POSITION 'R'
#define EVENT 'E'
#define BODY 'B'
#define ADDRESS 'A'
#define PORT 'P'



#define SENDER_POSITION_S "S"
#define RECEIVER_POSITION_S "R"
#define EVENT_S "E"
#define BODY_S "B"
#define ADDRESS_S "A"
#define PORT_S "P"


#define INTERFACE 0
#define BROADCAST 0
#define STAMP_MESSAGE _position, BROADCAST, EventType::None, _id, BROADCAST
#define LEADER_POSITION 1
#define NEW_LEADER_POSITION 2

#define NULL_POSITION 9

#define BUFFER_SIZE 2048

typedef float speedType;

typedef float stearingAngleType;

typedef float distanceType;


typedef enum
{
    MODE_TRUCK,
    MODE_LEADER
} simMode;


// Type of the events that could happen during the interaction between trucks in the platoon
enum  EventType
{
    LeaderElection = 97,
    LeaderElected = 98,
    Joining = 99, 
    Leaving=100, 
    Coupling=101,
    Decoupling=102,
    NewPlatoon=103,
    PlatoonNotFound=104,
    PlatoonFound =105,
    ReceivePosition=106,
    BroadcastInfo=107,
    Joined=108,
    None=109, 
    Crash=110,
    CommunicationFailure=111, 
    InterfaceInfo = 112,
    IamAlive = 113,
    Pin = 114,
    TruckDead = 115,
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
    case EventType::ReceivePosition:
        return outs<<"ReceivePosition";
    case EventType::Joined:
        return outs<<"Joined";
    case EventType::BroadcastInfo:
        return outs<<"BroadcastInfo";
    case EventType::None:
        return outs << "None";
    default:
        return outs << "No Event";
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
    ElectNewLeader, 
    PositionReceived
};
class Event
{
public:
    Event() {};
    Event(EventType Token){_Event = Token;};
    //EventType Type(){return _Event;};
    EventType Type()const {return _Event;};
protected:
    EventType _Event;

};

namespace TruckOMP {

    struct Message
    {
                Message(u_int16_t SenderPosition, u_int16_t ReceiverPosition, Event Event,u_int16_t SenderID = -1, u_int16_t ReceiverID = -1)
                : _SenderPosition(SenderPosition), _ReceiverPosition(ReceiverPosition), _Event(Event), _SenderID(SenderID),  _ReceiverID(ReceiverID)
                {};

                Message(){};
                u_int16_t _SenderPosition;
                u_int16_t _ReceiverPosition;
                Event _Event;
                int16_t _SenderID;
                int16_t _ReceiverID;
                std::string _Body;
    };
}


namespace TruckSocket
{
    struct Message
    {
        Message(){};
        Message(bool None) {if(!None) _Event = Event(EventType::None);};
        Message(std::map<std::string, std::string> map)
        {
            _SenderPosition = std::stoi(map[SENDER_POSITION_S]);
            _ReceiverPosition = std::stoi(map[RECEIVER_POSITION_S]);
            char char_array[map[EVENT_S].length()+ 1];
            strcpy(char_array, map[EVENT_S].c_str());
            _Event = Event(static_cast<EventType>(int(*char_array)));
            _Body = map[BODY_S];
            _Address = map[ADDRESS_S];
            _Port = std::stoi(map[PORT_S]);
        }
        int _SenderPosition;
        int _ReceiverPosition;
        Event _Event;
        std::string _Body;
        std::string _Address;
        unsigned int _Port;

        void ToBuffer  (char *buffer) const
        {
            buffer[0] = '{';
            buffer[1] = '\"';
            buffer[2] = SENDER_POSITION;
            buffer[3] = '\"';
            buffer[4] = ':';
            buffer[5] = '\"';
            buffer[6] = _SenderPosition+'0'; //Let's find a better way for position > 255
            buffer[7] = '\"';
            buffer[8] =',';
            buffer[9] = '\"';
            buffer[10] = RECEIVER_POSITION;
            buffer[11] = '\"';
            buffer[12] = ':';
            buffer[13] = '\"';
            buffer[14] = _ReceiverPosition + '0';//Let's find a better way for position > 255
            buffer[15] = '\"';
            buffer[16] = ',';
            buffer[17] = '\"';
            buffer[18] = EVENT;
            buffer[19] = '\"';
            buffer[20] = ':';
            buffer[21] = '\"';
            buffer[22] = static_cast<int>(_Event.Type());
            buffer[23] = '\"';
            buffer[24] = ',';

            buffer[25] = '\"';
            buffer[26] = ADDRESS;
            buffer[27] = '\"';
            buffer[28] = ':';
            buffer[29] = '\"';
            memcpy(buffer+30,_Address.c_str(),_Address.size() );
            buffer += _Address.size()+30;
            *buffer = '\"';
            buffer++;
            *buffer = ',';
            buffer++;
            *buffer = '\"';
            buffer++;
            *buffer = PORT;
            buffer++;
            *buffer = '\"';
            buffer++;
            *buffer = ':';
            buffer++;
            *buffer = '\"';
            buffer++;
            memcpy(buffer,std::to_string((int)_Port).c_str(),std::to_string(_Port).size() );
            buffer+= std::to_string(_Port).size();
            *buffer = '\"';
            buffer++;
            *buffer = ',';
            buffer++;
            *buffer  = '\"';
            buffer++;
            *buffer = BODY;
            buffer++;
            *buffer = '\"';
            buffer++;
            *buffer = ':';
            buffer++;
            memcpy(buffer,_Body.c_str(),_Body.size() ); 
            buffer+=_Body.size();
            *buffer= '}';
            buffer++;
            memcpy(buffer,"\n",2 ); 
        }
   
        bool operator< (Message const &m){return _SenderPosition < m._SenderPosition;}; //for sorting the queue based on the sender position
    };

    struct RawMessage
    {
        RawMessage(struct sockaddr_in sender, char* body)
        {
            this->body = body;
            this->sender = sender;
        }
        struct sockaddr_in sender;
        char* body;
    };
}


#endif




