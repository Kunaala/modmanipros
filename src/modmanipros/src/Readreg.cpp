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



Readreg::Readreg(Modbus::Slave* slv)
{
     std::cout<<"Reading has started\n";
     
     slave=slv;
     //Readreg::readVal(10);
   
}
std::vector<float> Readreg::readVal(std::vector<int> regAddr)
{
    uint16_t valread[4]; 
    std::vector <float> val(regAddr.size());
    std::string temp,temp1,temp2;
    for(int i=0;i<regAddr.size();i++)
    {
        if (slave->readInputRegisters(regAddr[i], valread, 2) == 2) {

        temp1=std::to_string(valread[0]);
        temp2=std::to_string(valread[1]);
        
        std::cout << i   <<": " << temp1 << std::endl;
        std::cout << i+1 <<": " << temp2 << std::endl;
        
        temp=temp1+"."+temp2;
        
        val[i]=std::stof(temp);
        
        std::cout<<val[i]<<std::endl;
        
    }
    else {
        
        std::cerr << "Unable to read input registers !" <<i<< std::endl;
        exit (EXIT_FAILURE);
        
    }
    }
    return val;
    
}

void Readreg::readBits(int regAddr)
{
    
}





