#include <iostream>
#include "TruckPlatoon.hpp"
//#include "src/utils/json.hpp"




int main()
{
    
    TruckPlatoon::StartSimulation(TruckPlatoon::Simulation::CreatePlatoon, TruckPlatoon::SOCKET);
    return 0;
} 

