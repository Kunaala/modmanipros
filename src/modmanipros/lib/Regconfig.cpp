
/*
 * Copyright 2020 chetan <chetanchadha@curlanalytics.com>
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

#include "Regconfig.h"
#include <fstream>

Regconfig::Regconfig()
{
    std::fstream file; 
	file.open("Gfg.txt",std::ios::out);
    Regconfig::handle = INI_New(NULL);
    // Read from file
    if(!INI_ReadFilePath(handle,"emerson.ini"))
    {
        // Free allocated memory
        INI_Free(handle);
        //return EXIT_FAILURE;
    }

}


int Regconfig::iniVal(const char* key,const char* sector = "rreg")
{
    return std::stoi(INI_GetString(Regconfig::handle, sector, key));
}

std::map<std::string, int> Regconfig::rwReg()
{
	std::map<std::string, int> regAddr;
	regAddr.insert(std::make_pair("instval.mflow", Regconfig::iniVal("instval_mflow")));
	regAddr.insert(std::make_pair("instval.density", Regconfig::iniVal("instval_density")));
	regAddr.insert(std::make_pair("instval.temp", Regconfig::iniVal("instval_temp")));
	regAddr.insert(std::make_pair("instval.vflow", Regconfig::iniVal("instval_vflow")));
	regAddr.insert(std::make_pair("instval.driveg",Regconfig::iniVal("instval_driveg")));
	regAddr.insert(std::make_pair("instval.rtfreq",Regconfig::iniVal("instval_rtfreq")));
	regAddr.insert(std::make_pair("instval.lpvolts", Regconfig::iniVal("instval_lpvolts")));
	regAddr.insert(std::make_pair("instval.rpvolts", Regconfig::iniVal("instval_rpvolts")));
	regAddr.insert(std::make_pair("totval.mflowt", Regconfig::iniVal("totval_mflowt")));
	regAddr.insert(std::make_pair("totval.mflowinv", Regconfig::iniVal("totval_mflowinv")));
	regAddr.insert(std::make_pair("totval.vflowt", Regconfig::iniVal("totval_vflowt")));
	regAddr.insert(std::make_pair("totval.vflowinv", Regconfig::iniVal("totval_vflowinv")));
	return regAddr;
}
 
std::vector<int> Regconfig::alarmReg()
{
	std::vector<int> reg = { 1,420}; 
	return reg;
}





 


