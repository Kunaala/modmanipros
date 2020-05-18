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

// const Setting& root = cfg.getRoot();

//   // Output a list of all books in the inventory.

//     const Setting& root = cfg.getRoot();

//   // Output a list of all books in the inventory.

//     const Setting &instValue = root["regType"]["readOnly"]["instValue"];
// 	std::vector<int> reg(12);
// 	instValue.lookupValue("massFlow", reg[0]);
// 	instValue.lookupValue("density", reg[1]);
//     instValue.lookupValue("temperature", reg[2]);
// 	instValue.lookupValue("volumeFlow", reg[3]);
// 	instValue.lookupValue("driveGain", reg[4]);
// 	instValue.lookupValue("tubeFrequency", reg[5]);
// 	instValue.lookupValue("lPickoff", reg[6]);
// 	instValue.lookupValue("rPickoff", reg[7]);
	
// 	const Setting &totValue = root["regType"]["readOnly"]["totValue"];
// 	totValue.lookupValue("massFlowTotal", reg[8]);
// 	totValue.lookupValue("massFlowInventory", reg[9]);
//     totValue.lookupValue("volumeTotal", reg[10]);
// 	totValue.lookupValue("volumeInventory", reg[11]);
// 	std::cout << reg[0] <<  reg[1] << reg[2] << reg[3] << std::endl;

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


// std::map<std::string, int> Regconfig::wReg()
// {
// // 	const Setting& root = cfg.getRoot();
// 
// //   // Output a list of all books in the inventory.
// 
// //     const Setting &readWrite = root["regType"]["readWrite"];
// // 	std::vector<int> reg(10);
// // 	readWrite.lookupValue("title", reg[0]);
// // 	readWrite.lookupValue("author", reg[1]);
// //     readWrite.lookupValue("price", reg[2]);
// // 	readWrite.lookupValue("qty", reg[3]);
// // 	std::cout << reg[0] <<  reg[1] << reg[2] << reg[3] << std::endl;
// // 	return reg;
// }
// 
// 
// 
// std::map<std::string, int> Regconfig::alarmReg()
// {
// 	// const Setting& root = cfg.getRoot();
//     // const Setting &readWrite = root["regType"]["alarm"];
// 	// std::vector<int> reg(10);
// 	// readWrite.lookupValue("title", reg[0]);
// 	// readWrite.lookupValue("author", reg[1]);
//     // readWrite.lookupValue("price", reg[2]);
// 	// readWrite.lookupValue("qty", reg[3]);
// 	// std::cout << reg[0] <<  reg[1] << reg[2] << reg[3] << std::endl;
// 	// return reg;
// }


 


