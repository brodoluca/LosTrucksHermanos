#ifndef SIMULATIONS_HPP
#define SIMULATIONS_HPP


#include "Truck.hpp"









namespace TruckOMP
{
    void TruckCreatesPlatoon(const int &NumberOfThreads = 4);
    void LeaderLeaves(const int &NumberOfTrucks = 4);
    void MemberLeaves(const int &NumberOfTrucks = 4);
}


namespace TruckSocket
{
    void TruckCreatesPlatoon(const int &NumberOfTrucks = 4);
    void LeaderLeaves(const int &NumberOfTrucks = 4);
    void MemberLeaves(const int &NumberOfTrucks = 4);    
}

#endif
