#include <iostream>
#include "TruckPlatoon.hpp"
//#include "src/utils/json.hpp"

typedef enum
{
    MODE_TRUCK,
    MODE_LEADER
} simMode;

int main(int argc, char *argv[])
{
    // default arguments
    simMode mode = MODE_TRUCK;
    int portNum = 11271;
    char *myIpAddr = (char *)"127.0.0.1";
    char *leaderIpAddr = (char *)"127.0.0.1";

    // parse arguments
    for (int i = 1; (i + 1) < argc; i += 2)
    {
        if (strcmp(argv[i], "--mode") == 0)
        {
            if (strcmp(argv[i + 1], "leader") == 0)
            {
                mode = MODE_LEADER;
            }
            else if (strcmp(argv[i + 1], "truck") == 0)
            {
                mode = MODE_TRUCK;
            }
        }
        else if (strcmp(argv[i], "--port") == 0)
        {
            // parse port number
            portNum = std::stoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--my_ip") == 0)
        {
            // parse IP number
            myIpAddr = argv[i + 1];
        }
        else if (strcmp(argv[i], "--leader_ip") == 0)
        {
            // parse IP number
            leaderIpAddr = argv[i + 1];
        }
    }

    // Execute
    if (mode == MODE_LEADER)
    {
        
        TruckSocket::Truck truck(1, "127.0.0.1", 11271);
        truck.CreatePlatoon();
        //TruckPlatoon::StartSimulation(TruckPlatoon::Simulation::CreatePlatoon, TruckPlatoon::SOCKET);
    }
    else if (mode == MODE_TRUCK)
    {
        // std::cout << "Mode: Truck; IP: " << ipAddr << "; Port: " << portNum << std::endl;
        TruckSocket::Truck truck(1, myIpAddr, 8765);
        truck.RequestToJoin(leaderIpAddr, portNum);
        // truck.LeavePlatoon(leaderIpAddr, portNum);
        // truck.Exist();
    }
    return 0;
}
