#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/serialization.h>
#include <ros_type_introspection/ros_introspection.hpp>
#include "modmanipros/regval.h"
#include "modmanipros/alarmval.h"
#include <string>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <regex> 
#include <iterator>
#include<exception>
#include<bsoncxx/exception/exception.hpp> 
#include<sstream>
#define BOOST_CHRONO_VERSION 2
#include<boost/chrono.hpp>
using namespace RosIntrospection;
using namespace ros::message_traits;
namespace ser = ros::serialization;
class Storereg
{   private:
        //mongocxx::collection collect;
        //mongocxx::client *clienttemp;
        void updatedb(bsoncxx::document::value doc_val,std::string collname);
        std::string dburi,dbname;
        int sid;
        
    public:
        void insertVal(const modmanipros::regval msg, const FlatMessage& fmsg);
        void insertVal(const modmanipros::alarmval msg, const FlatMessage& fmsg);

         mongocxx::client *clienttemp;
        Storereg(std::string mongouri,std::string mongodb); 
        void updatesid(std::string collname,std::string field);
        template<typename T> void deserialize(const T msg);
        void insertRegData(const modmanipros::regval msg);
        void insertAlarmData(const modmanipros::alarmval msg);
};
