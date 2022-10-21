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





void TruckCreatesPlatoon(const int &NumberOfThreads = 4);



#endif
