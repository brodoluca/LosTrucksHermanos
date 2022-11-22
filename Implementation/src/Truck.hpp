#ifndef TRUCK_HPP
#define TRUCK_HPP

#include "utils/include.hpp"


namespace TruckOMP
{
/// Class generated from the class diagram. 
class Truck
{
public:
    Truck();
    Truck(u_int16_t newID);
    u_int16_t GetID();
    void SetID(u_int16_t newID);

    speedType GetSpeed();
    stearingAngleType GetAngle();
    distanceType GetDistance();
    TruckState GetState();

    u_int16_t GetPosition();
    bool isLeader();

    void SetSpeed(speedType newSpeed);
    void SetAngle(stearingAngleType newStearingAngle);
    void SetDistance(distanceType newDistance);
    void SetState(TruckState newState);


    /// @brief Responsible for handling the events like in the state machine (Check the uml diagrams to learn better). 
    /// Responsible for the transitions basically.
    /// @param event 
    void HandleEvent(const TruckEvent &event);
    /// @brief Once the transition happens, see above, we are in a new state and we update the behavior. Meaning, we are in a state
    /// and we do some behavior in this state. 
    void Update();


    /// @brief All of the functions are place holders. As of right now, we do not have a mean of communication to send messages, 
    /// However, we have a work around using the vector. In the future, these need to be modified using the protocol we define. 
    /// @param Bus 
    void ReadBus(std::vector<Message>* Bus);
    //void WriteBus(std::vector<Message>* Bus,u_int16_t SenderPosition, u_int16_t ReceiverPosition, Event Event);
    void WriteBus(std::vector<Message>* Bus,u_int16_t SenderPosition, u_int16_t ReceiverPosition, Event Event, int16_t SenderID = -1, int16_t ReceiverID = -1 );
    void WriteBus(std::vector<Message>* Bus, Message *m );
    bool SearchFor(std::vector<Message>* Bus, const EventType& Event);
    Message PopBackLastMessage(std::vector<Message>* Bus);
    
    void SetBus(std::vector<Message>* Bus);



    ///@brief Checks whether a platoon exists or not. Right now, we do that by simply checking if there are messages on the bus. 
    ///        We will update it in the future
    void CheckPlatoon(std::vector<Message>* Bus);


    void BroadcastInfo();
    void Leave();
    


protected:
    TruckState _state;
    /// Each truck has its id and its position in the platoon. They are not necessarely the same thing
    u_int16_t _id;
    u_int16_t _position;
    u_int16_t _leaderID;
    speedType _speed;
    stearingAngleType _stearingAngle;
    distanceType _distance;

    constexpr static distanceType _safetyDistance = 150;//in m
    
    bool _isLeader = false;
    u_int16_t _platoonSize;
    std::vector<Message>* _Bus;
    
    void _updateSpeed(const speedType& newSpeed);
};
}// end of namespace


//////////////////////////////////////////////////////////////////


namespace TruckSocket
{

class Truck
{
public:
    Truck(const std::string& myAddress = "10.208.1.206", int port = 4321);
    Truck(u_int16_t newID, const std::string& myAddress = "169.254.39.55", int port = 4324);
    u_int16_t GetID();
    void SetID(u_int16_t newID);

    speedType GetSpeed();
    stearingAngleType GetAngle();
    distanceType GetDistance();
    TruckState GetState();
    bool isLeader();
    u_int16_t GetPosition();

    void SetSpeed(speedType newSpeed);
    void SetAngle(stearingAngleType newStearingAngle);
    void SetDistance(distanceType newDistance);
    void SetState(TruckState newState);

    void TruckServer();
    
    void Exist();
    void React(const Message& message);
    void Update();
    void HandleRawMessages();
    void HandleMessages();
    ~Truck();


    void RequestToJoin(const std::string& address, int port);
    void CreatePlatoon();


    bool Send(char* buffer );
    bool Send(const Message& message, int position);
    bool Send(const Message& message, const std::string& address, int port);
    bool Broadcast(const Message& message);

    bool BroadcastInfo();
    bool SendInfoToInterface( const std::string& InterfaceAddress, int InterfacePort);
protected:
    TruckState _state;
    /// Each truck has its id and its position in the platoon. They are not necessarely the same thing
    u_int16_t _id;
    u_int16_t _position;
    u_int16_t _leaderID;
    speedType _speed;
    stearingAngleType _stearingAngle;
    distanceType _distance;
    std::string _myAddress;
    unsigned int _myPort;

    constexpr static distanceType _safetyDistance = 150;//in m
    
    bool _isLeader = false;
    u_int16_t _platoonSize;

    std::thread* myServer;
    std::mutex lockAddresses;
    std::mutex lockMessageQueue;


    std::map<int, std::pair<std::string, int>> _Platoon;
    //std::vector< struct sockaddr_in> addressesOtherTrucks;
    struct sockaddr_in myServerAddress;
    int serverSocket;

    std::queue<Message> MessageQueue;
    std::queue<RawMessage> RawMessageQueue;

    time_t _lastTimeInfo;
    double _timeSinceLastInfo;
};


} //end of namespace


#endif