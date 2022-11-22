#include "Simulations.hpp"

namespace TruckOMP
{
static void ReadTheBus(const std::vector<Message>& MessageBus)
{
    std::cout << std::endl<<std::endl << "READING THE BUS: "<< std::endl <<std::endl;
    for(auto message: MessageBus)
    {
        std::cout<<"_SenderPosition: " <<message._SenderPosition <<" _ReceiverPosition: "<<message._ReceiverPosition << " EVENT:  " << message._Event.Type();
        std::cout<<" _SenderID: " <<message._SenderID << " _ReceiverID: "<<message._ReceiverID;
        std::cout << " _Body:"<< message._Body<<std::endl;
            
    }
}

void TruckCreatesPlatoon(const int &NumberOfThreads)
{

        std::vector<Message> MessageBus;

        

        omp_set_num_threads(NumberOfThreads);
        #pragma omp parallel shared(MessageBus)
        {
            int ID = omp_get_thread_num();
            
            

            TruckOMP::Truck truck(ID);
            truck.SetBus(&MessageBus);

            #pragma omp critical
            //std::cout << "TRUCK:  " << truck.GetID()<<  std::endl;
            truck.CheckPlatoon(&MessageBus);

            #pragma omp critical
            truck.Update();


            #pragma omp critical
            truck.Update();

        }



        ReadTheBus(MessageBus);
} 



void LeaderLeaves(const int &NumberOfTrucks)
{
    std::vector<Message> MessageBus;
    omp_set_num_threads(NumberOfTrucks);
    #pragma omp parallel shared(MessageBus)
    {
        int ID = omp_get_thread_num();
            
            

        TruckOMP::Truck *truck = new TruckOMP::Truck(ID);
        
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


    ReadTheBus(MessageBus);
}

void MemberLeaves(const int &NumberOfTrucks)
{
    std::vector<Message> MessageBus;
    omp_set_num_threads(NumberOfTrucks);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(2,NumberOfTrucks); // distribution in range [1, NumberOfTrucks]
    auto truckThatLeaves = int(dist6(rng));

    #pragma omp parallel shared(MessageBus)
    {
        int ID = omp_get_thread_num();
            
            

        TruckOMP::Truck *truck = new TruckOMP::Truck(ID);
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
        if(truck->GetPosition() == truckThatLeaves)
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
    ReadTheBus(MessageBus);
}

} // end of namespace






namespace TruckSocket
{
    void TruckCreatesPlatoon(const int &NumberOfTrucks)
    {
        Truck truck(1, "169.254.39.55", 1231);
        truck.CreatePlatoon();
    }
    void LeaderLeaves(const int &NumberOfTrucks)
    {
        std::cout << "WORK IN PROGRESS" << std::endl;
    }
    void MemberLeaves(const int &NumberOfTrucks)
    {
        
        std::cout << "WORK IN PROGRESS" << std::endl;
    }
} // end of namespace


