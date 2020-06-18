
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
Regconfig::Regconfig()
{
    
    Regconfig::handle = INI_New(NULL);
    // Read from file
    if(!INI_ReadFilePath(handle,"emerson.ini"))
    {
        // Free allocated memory
        INI_Free(handle);
        //return EXIT_FAILURE;
    }

}

// Regconfig::Regconfig(std::string fname)
// {
//     
//     INI* handle = INI_New(NULL);
//     // Read from file
//     if(!INI_ReadFilePath(handle,fname))
//     {
//         // Free allocated memory
//         INI_Free(handle);
//         //return EXIT_FAILURE;
//     }
// 
// }


std::map<std::string, int> Regconfig::rwReg()
{
	std::map<std::string, int> regAddr;
    std::string value;
    value = INI_GetString(handle, "rreg", "instval_mflow");
	regAddr.insert(std::make_pair("instval.mflow",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "instval_density");
	regAddr.insert(std::make_pair("instval.density",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "instval_temp");
	regAddr.insert(std::make_pair("instval.temp",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "instval_vflow");
	regAddr.insert(std::make_pair("instval.vflow",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "instval_driveg");
	regAddr.insert(std::make_pair("instval.driveg",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "instval_rtfreq");
	regAddr.insert(std::make_pair("instval.rtfreq",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "instval_lpvolts");
	regAddr.insert(std::make_pair("instval.lpvolts",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "instval_rpvolts");
	regAddr.insert(std::make_pair("instval.rpvolts",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "totval_mflowt");
	regAddr.insert(std::make_pair("totval.mflowt",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "totval_mflowinv");
	regAddr.insert(std::make_pair("totval.mflowinv",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "totval_vflowt");
	regAddr.insert(std::make_pair("totval.vflowt",std::stoi(value)));
    value = INI_GetString(handle, "rreg", "totval_vflowinv");
	regAddr.insert(std::make_pair("totval.vflowinv",std::stoi(value)));
	return regAddr;
}
 
std::vector<int> Regconfig::alarmReg()
{
	std::vector<int> reg = { 1,420}; 
	return reg;
}





 


