
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

	if (!config.Load("emerson.ini"))
	{
        std::cout<<"error opening file"<<std::endl;

	}

}


int Regconfig::iniVal(const char* key,const char* sector = "rreg")
{
    //return std::stoi(INI_GetString(Regconfig::handle, sector, key));
	return config.GetSection(sector)->GetValue(key).AsInt();
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
	std::vector<int> areg;
	INI::Array dval = config.GetSection("alarmreg")->GetValue("areg").AsArray();
	for(int i=0;i<dval.Size();i++)
	{
		areg.push_back(dval[i].AsInt()); 
	}
	
	return areg;
}

std::map<std::string,uint16_t> Regconfig::alarmConfig()
{
	std::map<std::string,uint16_t> regSeverity;
	regSeverity.insert(std::make_pair("125_9", 2));
	regSeverity.insert(std::make_pair("1_2", 3));
	regSeverity.insert(std::make_pair("1_4", 5));
	regSeverity.insert(std::make_pair("1_6", 6));
	regSeverity.insert(std::make_pair("1_10", 8));
	regSeverity.insert(std::make_pair("125_4", 8));
	regSeverity.insert(std::make_pair("1_14", 9));
	regSeverity.insert(std::make_pair("126_3", 27));
	regSeverity.insert(std::make_pair("125_0", 100));
	regSeverity.insert(std::make_pair("125_2", 101));
	regSeverity.insert(std::make_pair("125_5", 102));
	regSeverity.insert(std::make_pair("126_14", 104));
	regSeverity.insert(std::make_pair("126_15", 105));
	regSeverity.insert(std::make_pair("1_13", 105));
	regSeverity.insert(std::make_pair("126_0", 106));
	regSeverity.insert(std::make_pair("126_1", 107));
	regSeverity.insert(std::make_pair("126_6", 108));
	regSeverity.insert(std::make_pair("126_5", 109));
	regSeverity.insert(std::make_pair("125_13", 110));
	regSeverity.insert(std::make_pair("125_1", 113));
	regSeverity.insert(std::make_pair("125_3", 114));
	regSeverity.insert(std::make_pair("125_7", 115));
	return regSeverity;
}





 


