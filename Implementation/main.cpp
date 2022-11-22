#include <iostream>
#include "TruckPlatoon.hpp"
//#include "src/utils/json.hpp"




int main(int argc, char *argv[])
{
    if(argc <2) return 1;
    if(strcmp ( argv[1], "--mode") !=0)
    {
        std::cout << argv[1];
        return 1;
    }

    if(strcmp ( argv[2], "leader") ==0) TruckPlatoon::StartSimulation(TruckPlatoon::Simulation::CreatePlatoon, TruckPlatoon::SOCKET);
    if(strcmp ( argv[2], "truck") ==0)
    {
        if(argc !=5 )return 1;
        if(strcmp ( argv[3], "--port") ==0) 
        {
            TruckSocket::Truck truck(1, "127.0.0.1", 4567);
            truck.RequestToJoin("10.118.132.193", 17241);
            //truck.Exist();
        }
    }
    return 0;
} 

