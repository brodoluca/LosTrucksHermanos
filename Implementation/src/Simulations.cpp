#include "Simulations.hpp"


void TruckCreatesPlatoon(const int &NumberOfThreads)
{

        std::vector<Message> MessageBus;

        

        omp_set_num_threads(NumberOfThreads);
        #pragma omp parallel shared(MessageBus)
        {
            int ID = omp_get_thread_num();
            
            

            Truck truck(ID);
            truck.SetBus(&MessageBus);

            #pragma omp critical
            //std::cout << "TRUCK:  " << truck.GetID()<<  std::endl;
            truck.CheckPlatoon(&MessageBus);

        }

        std::cout << std::endl<<std::endl << "READING THE BUS: "<< std::endl <<std::endl;
        for(auto message: MessageBus)
        {
            std::cout<<"_SenderPosition: " <<message._SenderPosition <<" _ReceiverPosition: "<<message._ReceiverPosition << " EVENT:  " << message._Event.Type();
            std::cout<<" _SenderID: " <<message._SenderID << " _ReceiverID: "<<message._ReceiverID<< std::endl;
        }
} 
