
#ifndef TRUCKPLATOON_HPP
#define TRUCKPLATOON_HPP

#include "src/Simulations.hpp"


namespace TruckPlatoon
{

    enum Simulation{
        CreatePlatoon, 
        JoinPlatoon, 
        MemberLeavesPlatoon, 
        LeaderLeavesPlatoon
    };

    
    void StartSimulation( Simulation Option)
    {
        switch (Option)
        {
        case Simulation::CreatePlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// One truck creates the platoon //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckCreatesPlatoon(1);
            break;

        case Simulation::JoinPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// One truck creates the platoon //"<<std::endl;
            std::cout << "// Other 4 join                  //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            TruckCreatesPlatoon(5);
            break;
        
        case Simulation::MemberLeavesPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// Member Leaves the platoon     //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            MemberLeaves();
            break;
        case Simulation::LeaderLeavesPlatoon:
            std::cout << "///////////////////////////////////"<<std::endl;
            std::cout << "// Leader Leaves the platoon     //"<<std::endl;
            std::cout << "///////////////////////////////////"<<std::endl;
            LeaderLeaves();
            break;

        
        default:
            break;
        }
    }






 


    


}


#endif