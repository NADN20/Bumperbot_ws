#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "chrono" 
using namespace std::chrono_literals;
class Simple_Publisher : public rclcpp::Node
{

public:
    Simple_Publisher() : Node("SimplePublisher"), counter_(0)
    {
        pub_ = create_publisher<std_msgs::msg::String>("chatter", 10);
        timer_ =create_wall_timer(1s,bind(&Simple_Publisher::timercallback,this));
    }

private:
    size_t counter_;
    std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> pub_;
    std::shared_ptr<rclcpp::TimerBase> timer_ ; 

 void timercallback() {
   auto message = std_msgs::msg::String() ; 
   message.data= "Hello i can hear you - counter : " + std::to_string(counter_++) ; 
   pub_ ->publish(message) ; 

 }

};

int main(int argc,char* argv[]) {
 rclcpp::init(argc ,argv );
auto node = std::make_shared<Simple_Publisher> () ;
rclcpp::spin(node); 
rclcpp::shutdown(); 
}
