#include <libconfig.h++>
#include "Readreg.h"
#include "Regconfig.h"
#include<string>
#include<iostream>
#include<modbuspp.h>
#include<map>
#include<vector>



using namespace Modbus;
using namespace libconfig;

int main (int argc, char **argv) {
    std::string port ="/dev/pts/6";
    Master mb (Rtu, port , "38400"); // new master on RTU
    Slave  &slv = mb.addSlave(33);   // to the slave at address 33
	//std::vector<float> rwRegVal;
	Regconfig rc1;
	std::map<std::string, int> rRegisters,alarmRegisters;
    rRegisters = rc1.rwReg(); // to store the rw register address
	//alarmRegisters = rc1.alarmReg(); // to store alarm register address

    if (mb.open ()) { // open a connection
            
        Readreg r1(&slv);
        r1.readVal(rRegisters);
        mb.close();
    }
    else {
        std::cerr << "Unable to open MODBUS connection to " << port << std::endl;
        exit (EXIT_FAILURE);
    }

    return 0;
}
