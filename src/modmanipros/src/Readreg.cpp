/*
 * Copyright 2020 kunaala <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Readreg.h"
#include "ros/ros.h"
#include "modmanipros/regval.h"

Readreg::Readreg(Modbus::Slave* slv)
{
     std::cout<<"Reading has started\n";
     
     slave=slv;
     //Readreg::readVal(10);
   
}
float Readreg::readAddr(int addr)
{
    uint16_t valread[4]; 
    std::string temp,temp1,temp2;
    if (slave->readInputRegisters(addr, valread, 2) == 2) 
    {
        temp1=std::to_string(valread[0]);
        temp2=std::to_string(valread[1]);
        std::cout << i   <<": " << temp1 << std::endl;
        std::cout << i+1 <<": " << temp2 << std::endl;
        temp=temp1+"."+temp2;
        return std::stof(temp);
    }
    else 
    {
        std::cerr << "Unable to read input registers !" <<i<< std::endl;
        exit (EXIT_FAILURE);
    }
}
std::vector<float> Readreg::readVal(std::map<std::string, int> regAddr)
{
    std::vector <float> val(regAddr.size());
    modmanipros::regval msg;
    std::map<string, int>::const_iterator m;
    for(m = regAddr.begin(); m!=regAddr.end(); m++ )
    {
        msg.(m->first) = Readreg::readAddr(find(m));
    }
    
    return val;
    
}

void Readreg::readBits(std::vector<int> regAddr)
{
   uint16_t *valread = nullptr;
   std::vector<float> val(regAddr.size());
   for(int i = 0;i<regAddr.size();i++)
   {
	   if(slave->readInputRegisters(regAddr[i],valread,1) == 1)
	   {
		   for(int j = 0;j<16;j++)
		   {
			   std::cout<<"Reg "<<i<<" bit:"<<j<< static_cast<bool>(*valread & (1 << j)) << std::endl;
		   }
	   }
   }
   
   
}



