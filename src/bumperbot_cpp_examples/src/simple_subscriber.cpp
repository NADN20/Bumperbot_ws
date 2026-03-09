#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SimpleSubscriber : public rclcpp::Node
{

public:
    SimpleSubscriber() : Node("simple_subscriber")
    {
        sub_ = create_subscription<std_msgs::msg::String>("chatter", 10, bind(&SimpleSubscriber::msgcallback, this,std::placeholders::_1));
    }

private:
    std::shared_ptr<rclcpp::Subscription<std_msgs::msg::String>> sub_;
    void msgcallback(const std_msgs::msg::String & msg ) const {

        RCLCPP_INFO_STREAM(get_logger(),"I heard " <<  msg.data.c_str()) ; 
    };

};

int main(int argc,char* argv[]) {
    rclcpp::init(argc ,argv );
   auto node = std::make_shared<SimpleSubscriber> () ;
   rclcpp::spin(node); 
   rclcpp::shutdown(); 
   }