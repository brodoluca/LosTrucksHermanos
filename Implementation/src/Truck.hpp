
#ifndef TRUCK_HPP
#define TRUCK_HPP
#include "utils/PlatoonTypes.hpp"
#include "utils/Include.hpp"
#include <cstdint>




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

    bool CheckForPlatoon();
    
protected:
    TruckState _state;
    u_int16_t _id;
    speedType _speed;
    stearingAngleType _stearingAngle;
    distanceType _distance;
    
};



#endif