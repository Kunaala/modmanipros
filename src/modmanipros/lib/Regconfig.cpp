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

}

std::map<std::string, int> Regconfig::rwReg()
{


	std::map<std::string, int> regAddr;
	regAddr.insert(std::make_pair("instval.mflow",247));
	regAddr.insert(std::make_pair("instval.density",249));
	regAddr.insert(std::make_pair("instval.temp",251));
	regAddr.insert(std::make_pair("instval.vflow",253));
	regAddr.insert(std::make_pair("instval.driveg",291));
	regAddr.insert(std::make_pair("instval.rtfreq",285));
	regAddr.insert(std::make_pair("instval.lpvolts",287));
	regAddr.insert(std::make_pair("instval.rpvolts",289));
	regAddr.insert(std::make_pair("totval.mflowt",259));
	regAddr.insert(std::make_pair("totval.mflowinv",263));
	regAddr.insert(std::make_pair("totval.vflowt",261));
	regAddr.insert(std::make_pair("totval.vflowinv",265));
	return regAddr;
}
 
std::vector<int> Regconfig::alarmReg()
{
	std::vector<int> reg = { 1,420}; 
	return reg;
}


 


