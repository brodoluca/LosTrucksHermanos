
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
            TruckCreatesPlatoon(5);
            break;

        case Simulation::JoinPlatoon:
            TruckCreatesPlatoon(5);
            break;
        
        case Simulation::MemberLeavesPlatoon:
            TruckCreatesPlatoon(5);
            break;
        case Simulation::LeaderLeavesPlatoon:
            TruckCreatesPlatoon(5);
            break;

        
        default:
            break;
        }
    }







 


    


}


#endif