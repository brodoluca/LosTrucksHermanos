
#ifndef TRUCK_HPP
#define TRUCK_HPP
#include "utils/PlatoonTypes.hpp"
#include "utils/Include.hpp"
#include <cstdint>


//#include "Communication.hpp"

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



    void HandleEvent(const TruckEvent &event);
    void Update();

    void CheckPlatoon(std::vector<Message>* Bus);
    void ReadBus(std::vector<Message>* Bus);
    void WriteBus(std::vector<Message>* Bus,u_int16_t ID_Sender, u_int16_t ID_Receiver, Event Event);
    void WriteBus(std::vector<Message>* Bus, Message *m );
    
protected:
    TruckState _state;
    u_int16_t _id;
    speedType _speed;
    stearingAngleType _stearingAngle;
    distanceType _distance;

    u_int16_t _order;
    
};



#endif