#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include <chrono>
#include <memory>
#include <vector>
#include <string>
#include <map>

#include <thread>
#include <chrono>
#include <functional>
#include <cstdio>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "message/msg/message.hpp"     
using namespace std::chrono_literals;
using std::placeholders::_1;



class Subscriber : public rclcpp::Node
{
  public:
    Subscriber(std::string nodeName = "DefaultNode", const int &interval= 1000)
    : Node(nodeName)
    {
        RCLCPP_INFO(this->get_logger(), "Subscribing to node: Platoon");    
        subscription_ = this->create_subscription<message::msg::Message>(
        "Platoon", 10, std::bind(&Subscriber::topic_callback, this, _1));
        _running = false;
        mThread = std::thread([this, interval] {
            while (1) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                break;
            }
            stop();
        });
     
    }
    void SubscribeTo ( std::string TopicName)
    {
        RCLCPP_INFO(this->get_logger(), "Subscribing to node: " + TopicName);    
        subscription_ = this->create_subscription<message::msg::Message>(
        TopicName, 10, std::bind(&Subscriber::topic_callback, this, _1));
    }
  private:
    void topic_callback(const message::msg::Message::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I am subscribed");
      //if(!_running) _running = true;

      /*
      Use this tutorial for the parameters
        https://roboticsbackend.com/ros2-rclcpp-parameter-callback/
      */
    }
    rclcpp::Subscription<message::msg::Message>::SharedPtr subscription_;


    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    std::thread mThread{};
    std::atomic_bool _running{};

    void stop() {
        if(_running)  mThread.join();
        else std::cout << "Kill the node";
        
    }
};


#endif