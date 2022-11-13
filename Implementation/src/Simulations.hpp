#ifndef SIMULATIONS_HPP
#define SIMULATIONS_HPP

#include "Leader.hpp"
#include "Truck.hpp"

#include "utils/PlatoonTypes.hpp"
#include "utils/Include.hpp"

#include "Event.hpp"
#include "DrivingEvent.hpp"
#include "OrganizationalEvent.hpp"
#include "SafetyCriticalEvent.hpp"

#include "Communication.hpp"

#include <pthread.h>
#include <vector>
#include <random>



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
