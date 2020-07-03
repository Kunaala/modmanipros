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

Readreg::Readreg(modbus_t *ctx)
{
     std::cout<<"Reading has started\n";
     
     context=ctx;                     ///initialization of Slave
   
}
float Readreg::readAddr(int addr)
{
    std::string temp,temp1,temp2;
    
    for(int i=0; i <2; i++)
    {
        int regResponse = modbus_read_registers(context, addr-1, 2, tempval);
        std::cout<<regResponse<<std::endl;
        try{
            if (regResponse == 2)           ///returns number of registers read
            {
                // temp1=std::to_string(tempval[0]);
                // //temp2=std::to_string(valread[1]);
                // std::cout<<temp1<<std::endl;
                // //std::cout<<temp1<<" "<<temp2<<std::endl;
                std::cout<<"SUCCESS"<<std::endl;
                float val = modbus_get_float_cdab(tempval);
                std::cout<<val<<std::endl;
                return val;

            }
            else 
            {
                std::cerr << "Unable to read input registers !" <<addr<<"and"<<addr+1<< std::endl;
                throw "Unable to read input registers !";
            }
        }
        catch (const char* msg) {
            std::cerr << msg << std::endl;
            // boost::this_thread::sleep( boost::posix_time::milliseconds(1000) );
            continue;
        }

    }
}
modmanipros::regval Readreg::readVal(std::map<std::string, int> regAddr)
{
    
    modmanipros::regval msg;
    std::stringstream temp1,temp2;
    temp1<<boost::chrono::time_fmt(boost::chrono::timezone::utc, "%D")<<boost::chrono::system_clock::now();
	temp1>>msg.date;
	temp2<<boost::chrono::time_fmt(boost::chrono::timezone::utc, "%H:%M:%S")<<boost::chrono::system_clock::now();
	temp2>>msg.time;
    std::unordered_map<std::string, double*> umap; 
    // inserting values by using [] operator 
	umap["instval.mflow"] = &msg.instantValue.massFlow;
	umap["instval.density"] = &msg.instantValue.density;
	umap["instval.vflow"] = &msg.instantValue.volumeFlow;
	umap["instval.driveg"] = &msg.instantValue.driveGain;
	umap["instval.temp"] = &msg.instantValue.temperature;
	umap["instval.rtfreq"] = &msg.instantValue.rawTubeFrequency;
	umap["instval.lpvolts"] = &msg.instantValue.leftPickoffVolt;
	umap["instval.rpvolts"] = &msg.instantValue.rightPickoffVolt;
	umap["totval.mflowt"] = &msg.totalValue.massFlowTotal;
	umap["totval.mflowinv"] = &msg.totalValue.massFlowInventory;
	umap["totval.vflowt"] = &msg.totalValue.volumeFlowTotal;
	umap["totval.vflowinv"] = &msg.totalValue.volumeFlowInventory;
	std::cout<<"In program"<<&msg<<std::endl;
	typedef std::map<std::string, int>::const_iterator map_itr;
    for(map_itr m = regAddr.begin(); m!=regAddr.end(); m++ )    ///iterating through each register and calling readAddr for each
    {
		float temp = Readreg::readAddr((m->second));
		*umap[m->first] = temp;
    }
    
    return msg;                                                 ///returns rosmsg to rostopic publisher  readregpub
    
}

modmanipros::alarmval Readreg::readBits(std::vector<int> regAddr, std::map<std::string, uint16_t> regSeverity)     ///Reading Alarm registers of 16bits to return the bits which are set to indicate error
{
    modmanipros::alarmval msg;
    std::vector<float> val(regAddr.size());
    std::string temp;
    std::vector<uint16_t> alarmval;
   for(int i = 0;i<regAddr.size();i++)
   {
      
            uint16_t valread[2];
            if(modbus_read_registers(context, regAddr[i]-1,1 , valread) == 1)
            {
                
                // alarmval = &msg.primaryflags;
                for(int j = 0;j<16;j++)
                {
                    bool bitval;
                     ///Bitmasking register to isolate individual bits(Alarms/Flags)
                    bitval = bool(valread[0] & (1 << j));
                    std::cout<<"Reg "<<regAddr[i]<<" bit:"<<j<<": "<< bitval<< std::endl; 
                    //bitval = bool(valread[0] & (1 << j));
                    
                    if(bitval)
                    {
                        temp=std::to_string(regAddr[i])+"_"+std::to_string(j);
                        std::map<std::string,uint16_t>::iterator it=regSeverity.find(temp);
                        if (it!=regSeverity.end())
                        {
                            alarmval.push_back(regSeverity.find(temp)->second);
                        }

                    }
                   
                } 
                
                
            }
   

   }
   msg.severity = alarmval;
   
   return msg;                                                           ///returns rosmsg to rostopic publisher alarmpub
}



