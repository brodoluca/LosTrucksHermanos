#include <cstdio>
#include "Platoon.hpp"
int main(int argc, char ** argv)
{
  
  rclcpp::init(0, nullptr);
  printf("hello world truck package\n");

  Truck truck(4);

  rclcpp::shutdown();
  return 0;
}
