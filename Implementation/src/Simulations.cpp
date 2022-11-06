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

            #pragma omp critical
            truck.Update();


            #pragma omp critical
            truck.Update();

        }



        std::cout << std::endl<<std::endl << "READING THE BUS: "<< std::endl <<std::endl;
        for(auto message: MessageBus)
        {
            std::cout<<"_SenderPosition: " <<message._SenderPosition <<" _ReceiverPosition: "<<message._ReceiverPosition << " EVENT:  " << message._Event.Type();
            std::cout<<" _SenderID: " <<message._SenderID << " _ReceiverID: "<<message._ReceiverID;
            std::cout << " _Body:"<< message._Body<<std::endl;
            
        }
} 



void LeaderLeaves(const int &NumberOfTrucks)
{
    std::vector<Message> MessageBus;
    omp_set_num_threads(NumberOfTrucks);
    #pragma omp parallel shared(MessageBus)
    {
        int ID = omp_get_thread_num();
            
            

        Truck *truck = new Truck(ID);
        truck->SetBus(&MessageBus);

        #pragma omp critical
        //std::cout << "TRUCK:  " << truck.GetID()<<  std::endl;
        truck->CheckPlatoon(&MessageBus);
        
        #pragma omp critical
        truck->Update();

        #pragma omp critical
        truck->Update();
        #pragma omp critical
        truck->Update();

        #pragma omp critical
        truck->Update();
        #pragma omp barrier
        #pragma omp critical
        if(truck->GetPosition() == LEADER_POSITION)
        {
            truck->Leave();
            //delete truck;
        }else
        {
            truck->Update();
        }
        #pragma omp barrier
        #pragma omp critical
        truck->Update();

        #pragma omp critical
        truck->Update();

        


    }


    std::cout << std::endl<<std::endl << "READING THE BUS: "<< std::endl <<std::endl;
    for(auto message: MessageBus)
    {
        std::cout<<"_SenderPosition: " <<message._SenderPosition <<" _ReceiverPosition: "<<message._ReceiverPosition << " EVENT:  " << message._Event.Type();
        std::cout<<" _SenderID: " <<message._SenderID << " _ReceiverID: "<<message._ReceiverID;
        std::cout << " _Body:"<< message._Body<<std::endl;
            
    }
}