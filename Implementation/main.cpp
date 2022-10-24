#include <iostream>
#include "TruckPlatoon.hpp"
//#include "src/utils/json.hpp"




int main()
{
    
    std::string Tags[] = {"Rules", "Ciao"};
    std::string Values[] = {"A", "A"};
    
    //std::string  t = StupidJSON::CreateJsonFromTags(Tags,Values, 2);
    //std::cout << t<< std::endl;;
    //auto json = json::parse(t)
    //auto m = ReadJson(t);
    //std::cout << m["Rules"];
    TruckPlatoon::StartSimulation(TruckPlatoon::Simulation::JoinPlatoon);
    return 0;
} 