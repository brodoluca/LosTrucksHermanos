#ifndef TRUCKSOCKET_HPP
#define TRUCKSOCKET_HPP
#include "utils/include.hpp"


#include "utils/include.hpp"




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
    void BroadcastNewPlatoonMember();
    
    void SharePlatoonMembers();
    
    bool SendInfoToInterface( const std::string& InterfaceAddress, int InterfacePort);
    void UpdatePlatoonPosition( int leavingTruck);
    
    bool SendAlive();
    void RemoveTruck(int position);
    void RemoveTruck(std::vector<int> position);
    void DebugInfo();
    
    void CheckAliveTime();
    
    
    void ReadDistanceSencor();
    
    void SlowDown(int distance);
    void SpeedUp(int distance);
    
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
    std::thread* distanceSensor;
    std::mutex lockAddresses;
    std::mutex lockMessageQueue;


    std::map<int, std::pair<std::string, int>> _Platoon;
    std::map<int, double> _PlatoonAliveTime;
    //std::vector< struct sockaddr_in> addressesOtherTrucks;
    struct sockaddr_in myServerAddress;
    int serverSocket;
    
    std::queue<Message> MessageQueue;
    std::queue<RawMessage> RawMessageQueue;
    std::queue<double> sensorReads;
    time_t _lastTimeInfo;
    double _lastAliveSent;
    
    
};


} //end of namespace


#endif
