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

#ifndef READREG_H
#define READREG_H

#include<string>
#include<iostream>
#include<modbus.h>
#include<map>
#include<vector>
#include<unordered_map>
#include "modmanipros/regval.h"
#include "modmanipros/alarm.h"

class Readreg
{
public:

   
    Readreg(modbus_t* ctx);
    modmanipros::regval readVal(std::map<std::string, int> regAddr);
    float readAddr(int addr);
	modmanipros::alarm readBits(std::vector<int> regAddr, std::map<std::string, uint16_t> regSeverity);
    
private:
    
    modbus_t *context;                                      ///creating local slave object
  
    uint16_t tempval[2];                    ///containers for reading value from registers

   


    
};

#endif // READREG_H
