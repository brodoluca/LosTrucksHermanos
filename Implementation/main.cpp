#include <iostream>
#include "TruckPlatoon.hpp"


int main()
{
    
    std::string Tags[] = {"Rules", "Ciao"};
    std::string Values[] = {"A", "A"};

    std::cout << CreateJsonFromTags(Tags,Values, 2) << std::endl;;

    TruckPlatoon::StartSimulation(TruckPlatoon::Simulation::CreatePlatoon);
    return 0;
}