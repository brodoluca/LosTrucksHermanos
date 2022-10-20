



#include "src/Leader.hpp"
#include "src/Truck.hpp"

#include "src/utils/PlatoonTypes.hpp"
#include "src/utils/Include.hpp"

#include "src/Event.hpp"
#include "src/DrivingEvent.hpp"
#include "src/OrganizationalEvent.hpp"
#include "src/SafetyCriticalEvent.hpp"

#include <pthread.h>

namespace TruckPlatoon
{

    void TruckCreatesPlatoon(const int &NumberOfThreads = 4);
    void StartSimulation( uint8_t Option)
    {
        switch (Option)
        {
        case 1:
            TruckCreatesPlatoon();
            break;
        
        default:
            break;
        }
    }


    

    void TruckCreatesPlatoon(const int &NumberOfThreads)
    {


        omp_set_num_threads(NumberOfThreads);
        #pragma omp parallel 
        {
            int ID = omp_get_thread_num();
            
            

            Truck truck(ID);

            #pragma omp barrier
            std::cout << "TRUCK:  " << truck.GetID();
            std::cout <<  std::endl;
            

        }
    } 


}