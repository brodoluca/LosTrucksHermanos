
#ifndef TRUCKPLATOON_HPP
#define TRUCKPLATOON_HPP

#include "src/Simulations.hpp"


typedef enum simMode{
    MODE_LEADER, 
    MODE_TRUCK
}simMode;

namespace TruckPlatoon
{
    bool OMP = true;
    bool SOCKET = false;
    enum Simulation{
        CreatePlatoon, 
        JoinPlatoon, 
        MemberLeavesPlatoon, 
        LeaderLeavesPlatoon
    };




    static void OMPSimulation(Simulation Option)
    {
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "//       OPENMP SIMULATION      //"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        switch (Option)
        {
        case Simulation::CreatePlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// One truck creates the platoon //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckOMP::TruckCreatesPlatoon(1);
            break;

        case Simulation::JoinPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// One truck creates the platoon //"<<std::endl;
            std::cout << "// Other 4 join                  //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckOMP::TruckCreatesPlatoon(5);
            break;
        
        case Simulation::MemberLeavesPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// Member Leaves the platoon     //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckOMP::MemberLeaves();
            break;
        case Simulation::LeaderLeavesPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// Leader Leaves the platoon     //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckOMP::LeaderLeaves();
            break;

        
        default:
            break;
        }
    }


     static void SocketSimulation(Simulation Option)
    {
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "//       SOCKET SIMULATION      //"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << "///////////////////////////////////"<<std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        switch (Option)
        {
        case Simulation::CreatePlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// One truck creates the platoon //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckSocket::TruckCreatesPlatoon(1);
            break;

        case Simulation::JoinPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// One truck creates the platoon //"<<std::endl;
            std::cout << "// Other 4 join                  //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckSocket::TruckCreatesPlatoon(5);
            break;
        
        case Simulation::MemberLeavesPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// Member Leaves the platoon     //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckSocket::MemberLeaves();
            break;
        case Simulation::LeaderLeavesPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// Leader Leaves the platoon     //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckSocket::LeaderLeaves();
            break;

        
        default:
            break;
        }
    }


    void StartSimulation( Simulation Option, bool OPENMP = false)
    {   
        if(OPENMP)
            OMPSimulation(Option);
        else
            SocketSimulation(Option);
    }


 


    


}


#endif