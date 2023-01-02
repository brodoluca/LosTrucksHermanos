#include <iostream>
#include "TruckPlatoon.hpp"
//#include "src/utils/json.hpp"

int main(int argc, char *argv[])
{
    // default arguments
    simMode mode = MODE_TRUCK;
    int leaderPortNum = 11271;
    int myPortNum = 11272;
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
            try
            {
                leaderPortNum = std::stoi(argv[i + 1]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error in port number" << '\n';
                return 1;
            }
        }
        else if (strcmp(argv[i], "--my_port") == 0)
        {
            // parse port number
            try
            {
                myPortNum = std::stoi(argv[i + 1]);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error in My port number" << '\n';
            }
            
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
        TruckSocket::Truck truck(1, leaderIpAddr, leaderPortNum);
        truck.CreatePlatoon();
        //TruckPlatoon::StartSimulation(TruckPlatoon::Simulation::CreatePlatoon, TruckPlatoon::SOCKET);
    }
    else if (mode == MODE_TRUCK)
    {
        TruckSocket::Truck truck(1, myIpAddr, myPortNum);
        truck.RequestToJoin(leaderIpAddr, leaderPortNum);
        // truck.LeavePlatoon(leaderIpAddr, leaderPortNum);
        // truck.Exist();
    }
    return 0;
}
