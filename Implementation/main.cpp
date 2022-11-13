#include <iostream>
#include "TruckPlatoon.hpp"
//#include "src/utils/json.hpp"




int main()
{
    
    TruckPlatoon::StartSimulation(TruckPlatoon::Simulation::MemberLeavesPlatoon, TruckPlatoon::SOCKET);
    return 0;
} 

