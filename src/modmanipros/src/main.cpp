#include <libconfig.h++>
#include "Readreg.h"
#include "Regconfig.h"



using namespace Modbus;
using namespace libconfig;

int main (int argc, char **argv) {
    std::string port ="/dev/pts/6";
    Master mb (Rtu, port , "38400"); // new master on RTU
    Slave  &slv = mb.addSlave(33);                          // to the slave at address 33

    
    if (mb.open ()) { // open a connection
            
        Readreg r1(&slv);
        Regconfig rc1;
        std::vector <int> reg;
        reg = rc1.rwReg();
        
        mb.close();
    }
    else {
        std::cerr << "Unable to open MODBUS connection to " << port << std::endl;
        exit (EXIT_FAILURE);
    }

    return 0;
}
