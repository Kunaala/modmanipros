#include "Readreg.h"
#include "writereg.h"
#include "Regconfig.h"
#include<string>
#include<iostream>
#include<modbuspp.h>
#include<map>
#include<vector>
#include<ros/ros.h>


using namespace Modbus;

int main (int argc, char **argv) {
    std::string port ="/dev/ttyUSB0";
    Master mb (Rtu, port , "38400"); /// new master on RTU
    Slave  &slv = mb.addSlave(1);   /// to the slave at address 33
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

    if (mb.open ()) {                       /// open a connection
        Readreg r1(&slv);
        ///ROS publisher
        while (ros::ok())
        {
            ///creating custom ros msg objects
            modmanipros::regval readRegMsg;
            modmanipros::alarm alarmMsg;
            readRegMsg= r1.readVal(rRegisters);         ///reading values of holding registers
            alarmMsg =  r1.readBits(alarmRegisters);    ///reading values of Alarm/flag registers
            ///Publishing values read libmodbuspp through ROS topics
            readregpub.publish(readRegMsg);
            alarmpub.publish(alarmMsg);
            ros::spinOnce();
            loop_rate.sleep();
        }
        ///End of ROS publisher//////
        mb.close();                         ///Close connection
    }
    else {
        std::cerr << "Unable to open MODBUS connection to " << port << std::endl;
        exit (EXIT_FAILURE);
    }

    return 0;
}
