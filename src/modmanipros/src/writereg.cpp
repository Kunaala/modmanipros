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

#include "writereg.h"


Writereg::Writereg(Modbus::Slave* slv)
{

     std::cout<<"Writing has started\n";
     
     slave=slv;
     //Readreg::readVal(10);
   

}

void Writereg::writeAddr(std::map<std::string, int> regAddr)
{
    int ret,i=0;
    for (int j=0;j<regAddr.size();j++)
    {
        inputs[j]=15;
        //std::cout<<"value at reg at position : "<<j<<"is"<<inputs[j];
    }

  typedef std::map<std::string, int>::const_iterator map_itr;
    for(map_itr m = regAddr.begin(); m!=regAddr.end(); m++ )
    { 
        //yet to add write error case 
        slave->writeRegisters(m->second,inputs,1);
        i++;
    
    }
}
