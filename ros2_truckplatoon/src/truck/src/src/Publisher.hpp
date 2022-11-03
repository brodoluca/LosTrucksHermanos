#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include <chrono>
#include <memory>
#include <vector>
#include <string>
#include <map>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/message.hpp"     // CHANGE
using namespace std::chrono_literals;



class Publisher : public rclcpp::Node
{
public:
  Publisher(std::string nodeName = "DefaultNode")
  : Node(nodeName)
  {
      RCLCPP_INFO(this->get_logger(), "Publishing node: Platoon");    // CHANGE
  std::string TopicName = "Platoon";
  name_=TopicName;
  publishers_[TopicName] = this->create_publisher<message::msg::Message>(TopicName, 10);
  timer_ = this->create_wall_timer(500ms, std::bind(&Publisher::callback, this));
  }
  /*
void PublishTo ( std::string TopicName)
{
  RCLCPP_INFO(this->get_logger(), "Publishing node: " + TopicName);    // CHANGE
  std::string TopicName2 = TopicName;

  publishers_[TopicName] = this->create_publisher<message::msg::Message>(TopicName, 10);
  timer_ = this->create_wall_timer(
    500ms, [this, &TopicName2]() -> void { this->callback(TopicName2); });
  
}
*/
void SendMessageTo( std::string TopicName)
{
  auto message = message::msg::Message();   
  message.sender_position = int16_t(0);
  message.receiver_position = int16_t(0);
  message.sender_id =int16_t(0);
  message.receiver_id = int16_t(0);
  //message.event = "PlatoonNotFound";
  RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.sender_position);    // CHANGE
  this->publishers_[TopicName]->publish(message);
}


private:
  void callback()
  {
    auto message = message::msg::Message();   
    message.sender_position = int16_t(0);
    message.receiver_position = int16_t(0);
    message.sender_id =int16_t(0);
    message.receiver_id = int16_t(0);
    //message.event = "PlatoonNotFound";
    RCLCPP_INFO(this->get_logger(), "here Publishing: '%d'", message.sender_position);    // CHANGE
    this->publishers_[name_]->publish(message);
  }

  std::string name_;
  rclcpp::TimerBase::SharedPtr timer_;
  //std::vector <rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr> publisherVector_;
  std::map<std::string, rclcpp::Publisher<message::msg::Message>::SharedPtr> publishers_;
};

//int main(int argc, char * argv[])
//{
  //rclcpp::init(argc, argv);
  //rclcpp::spin(std::make_shared<MinimalPublisher>());
  //rclcpp::shutdown();
  //return 0;
//}
#endif