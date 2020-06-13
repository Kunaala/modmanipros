#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/serialization.h>
#include <ros_type_introspection/ros_introspection.hpp>
#include "modmanipros/regval.h"
#include "modmanipros/alarm.h"
#include <string>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <regex> 
#include <iterator> 
using namespace RosIntrospection;
using namespace ros::message_traits;
namespace ser = ros::serialization;
class Storereg
{
    private:
        // mongocxx::client conn{mongocxx::uri{}};
    public:
	Storereg();
        bsoncxx::document::value deserialize(const modmanipros::regval msg);
        void insertRegData(const modmanipros::regval msg);
};
