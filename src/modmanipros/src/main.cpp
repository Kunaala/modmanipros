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
    modbus_t *ctx ;
    ctx = modbus_new_rtu("/dev/ttyTHS1", 38400, 'N', 8, 1);
    if (!ctx) {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }

//Set the Modbus address of the remote slave (to 3)
    modbus_set_slave(ctx, 1);
    ///ros inclusion
    ros::init(argc,argv,"modbusnode");
    ros::NodeHandle nh;
    ros::Rate loop_rate(1);
    ros::Publisher readregpub=nh.advertise<modmanipros::regval>("modmanip/readval",1000);
    ros::Publisher alarmpub=nh.advertise<modmanipros::alarm>("modmanip/alarm",1000);
    ///ros node initialized
	Regconfig rc1;         //initialization of config object
	std::map<std::string, int> rRegisters;   ///reading address of holding registers
    std::vector<int> alarmRegisters;         ///reading address of Alarm/flag registers
    rRegisters = rc1.rwReg();                /// to store the rw register address
    alarmRegisters = rc1.alarmReg();	    /// to store alarm register address
    Storereg db;
                    /// open a connection
    Readreg r1(ctx);
    ///ROS publisher
    while (ros::ok())
    {
        ///creating custom ros msg objects
        modmanipros::regval readRegMsg;
        modmanipros::alarm alarmMsg;
        readRegMsg= r1.readVal(rRegisters);         ///reading values of holding registers
        alarmMsg =  r1.readBits(alarmRegisters);    ///reading values of Alarm/flag registers
        db.insertRegData(readRegMsg);
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
