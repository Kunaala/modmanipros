#include <libconfig.h++>
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
using namespace libconfig;

int main (int argc, char **argv) {
    std::string port ="/dev/pts/12";
    Master mb (Rtu, port , "38400"); // new master on RTU
    Slave  &slv = mb.addSlave(33);   // to the slave at address 33
    /////ros inclusion//////
    ros::init(argc,argv,"modbusnode");
    ros::NodeHandle nh;
    ros::Rate loop_rate(0.2);
    ros::Publisher readregpub=nh.advertise<modmanipros::regval>("modmanip/readval",1000);
    /////ros node initialized////
	Regconfig rc1;
	std::map<std::string, int> rRegisters,alarmRegisters;
    rRegisters = rc1.rwReg(); // to store the rw register address
	//alarmRegisters = rc1.alarmReg(); // to store alarm register address

    if (mb.open ()) { // open a connection
            
        Writereg w1(&slv);
        Readreg r1(&slv);
        w1.writeAddr(rRegisters);
        ///ROS publisher//////////
        while (ros::ok())
        {
            
            modmanipros::regval msg;
            
            msg= r1.readVal(rRegisters);
            readregpub.publish(msg);
            ros::spinOnce();
            loop_rate.sleep();
        }
        ///End of ROS publisher//////
        mb.close();
    }
    else {
        std::cerr << "Unable to open MODBUS connection to " << port << std::endl;
        exit (EXIT_FAILURE);
    }

    return 0;
}
