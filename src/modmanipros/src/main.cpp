#include "Readreg.h"
#include "writereg.h"
#include "Regconfig.h"
#include "database.h"
#include<string>
#include<iostream>
#include<modbus.h>
#include<map>
#include<vector>
#include<ros/ros.h>


using namespace Modbus;

int main (int argc, char **argv) {

    ros::init(argc,argv,"modbusnode");
    ros::NodeHandle nh;
    ros::Rate loop_rate(1);
    ros::Publisher readregpub=nh.advertise<modmanipros::regval>("modmanip/readval",1000);
    ros::Publisher alarmpub=nh.advertise<modmanipros::alarm>("modmanip/alarm",1000);
    ///ros node initialized
    modbus_t *ctx ;
    std::string com_port;
    int baud_rate;
    std::string parity;
    nh.getParam("/com_port", com_port);
    nh.getParam("/baud_rate",baud_rate);
    nh.getParam("/parity",parity);
    //const char *tempcom=com_port.c_str();
    ctx = modbus_new_rtu(com_port.c_str(), baud_rate, parity[0], 8, 1);
    if (!ctx) {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }

    
    modbus_set_slave(ctx, 1);    //Set the Modbus address of the remote slave (to 1)
	Regconfig rc1;         //initialization of config object
	std::map<std::string, int> rRegisters;   ///reading address of holding registers
    std::map<std::string, uint16_t> alarmConfig; 
    std::vector<int> alarmRegisters;         ///reading address of Alarm/flag registers
    rRegisters = rc1.rwReg();                /// to store the rw register address
    alarmRegisters = rc1.alarmReg();	    /// to store alarm register address
    alarmConfig=rc1.alarmConfig();
    Storereg db;
                    /// open a connection
    Readreg r1(ctx);
    std::string dburi;
    std::string dbname;
    nh.getParam("/dburi", dburi);
    nh.getParam("/dbname",dbname);
   
    ///ROS publisher
    while (ros::ok())
    {
        ///creating custom ros msg objects
        modmanipros::regval readRegMsg;
        modmanipros::alarm alarmMsg;
        readRegMsg= r1.readVal(rRegisters);         ///reading values of holding registers
        alarmMsg =  r1.readBits(alarmRegisters, alarmConfig);    ///reading values of Alarm/flag registers
        db.insertRegData(readRegMsg,dburi,dbname);
        ///Publishing values read libmodbuspp through ROS topics
        readregpub.publish(readRegMsg);
        alarmpub.publish(alarmMsg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    ///End of ROS publisher//////   
                         ///Close connection
    modbus_close(ctx);
    modbus_free(ctx);
    
    return 0;
}
