#include <cuda.h>
#include <iostream>
#include <deque>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "./utils/types.hpp"
#include <thread>
#include "utils/types.hpp"
#include "utils/sorter.hpp"
#include <thrust/sort.h>
#include <thrust/copy.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <stdio.h>

void gpuSort(std::deque<TruckSocket::Message> &h_deque) {
  std::cout << "got not raw: "<<h_deque.size()<<" in dequq" << std::endl;
  if(h_deque.size()==0)return;
  int* h_distances = (int*) malloc(h_deque.size()*sizeof(int));
  int* d_distances;cudaMalloc((void**)d_distances, h_deque.size()*sizeof(int));

  for (int i = 0; i < h_deque.size(); i++){
    h_distances[i] = h_deque.at(i)._SenderPosition;
  }
  //copy h_distances to d_distances
  cudaMemcpy(d_distances, h_distances, h_deque.size()*sizeof(int), cudaMemcpyHostToDevice);
  //sort d_distances
  thrust::sort(d_distances, d_distances+h_deque.size());

  //copy d_distances to h_distances
  cudaMemcpy(h_distances, d_distances, h_deque.size()*sizeof(int), cudaMemcpyDeviceToHost);
  
  //manually sort the deque based on the sorted h_distances
  std::deque<TruckSocket::Message> temp_deque;
  for (int i = 0; i < h_deque.size(); i++){
    for (int j = 0; j < h_deque.size(); j++){
      if(h_distances[i] == h_deque.at(j)._SenderPosition){
        temp_deque.push_back(h_deque.at(j));
        break;
      }
    }
  }
  h_deque = temp_deque;
  free(h_distances);
  cudaFree(d_distances);

}

void gpuSort(std::deque<TruckSocket::RawMessage> &h_deque) {
  std::cout << "got raw: "<<h_deque.size()<<" in dequq" << std::endl;
  //returns nothing since no distance to be sorted
}

