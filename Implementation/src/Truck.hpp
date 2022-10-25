#ifndef TRUCK_HPP
#define TRUCK_HPP
#include "utils/PlatoonTypes.hpp"
#include "utils/Include.hpp"
#include <cstdint>

#include "utils/JsonHandler.hpp"


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

    bool isLeader();

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



#endif