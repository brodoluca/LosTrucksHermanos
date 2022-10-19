
#ifndef TRUCK_HPP
#define TRUCK_HPP

#include <cstdint>

class Truck
{
public:
    Truck();
    u_int16_t GetID();
    void SetID(u_int16_t newID);

    float GetSpeed();
    float GetAngle();
    float GetDistance();
    
protected:
    u_int16_t _id;
    float _speed;
    float _stearingAngle;
    float _distance;
};

#endif