



#include "src/Leader.hpp"
#include "src/Truck.hpp"

#include "src/utils/PlatoonTypes.hpp"
#include "src/utils/Include.hpp"

#include "src/Event.hpp"
#include "src/DrivingEvent.hpp"
#include "src/OrganizationalEvent.hpp"
#include "src/SafetyCriticalEvent.hpp"

#include "src/Communication.hpp"

#include <pthread.h>
#include <vector>
namespace TruckPlatoon
{

    void TruckCreatesPlatoon(const int &NumberOfThreads = 4);
    void StartSimulation( uint8_t Option)
    {
        switch (Option)
        {
        case 1:
            TruckCreatesPlatoon(5);
            break;
        
        default:
            break;
        }
    }







 


    void TruckCreatesPlatoon(const int &NumberOfThreads)
    {

        std::vector<Message> MessageBus;

        

        omp_set_num_threads(NumberOfThreads);
        #pragma omp parallel shared(MessageBus)
        {
            int ID = omp_get_thread_num();
            
            

            Truck truck(ID);


            #pragma omp critical
            //std::cout << "TRUCK:  " << truck.GetID()<<  std::endl;
            truck.CheckPlatoon(&MessageBus);

        }

        for(auto message: MessageBus)
        {
            std::cout<<"ID_Sender: " <<message._ID_Sender <<" ID_RECEIVER: "<<message._ID_Receiver << " EVENT:  " << message._Event.Type() << std::endl;
        }
    } 


}