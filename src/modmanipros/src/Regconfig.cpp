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

  // Read the file. If there is an error, report it and exit.
  try
  {
    cfg.readFile("invalid.cfg");
  }
  catch(const FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file." << std::endl;
  }
  catch(const ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine();
  }
}


std::vector<int> Regconfig::rwReg()
{
	const Setting& root = cfg.getRoot();

  // Output a list of all books in the inventory.

    const Setting &instValue = root["regType"]["readOnly"]["instValue"];
	std::vector<int> reg(10);
	instValue.lookupValue("title", reg[0]);
	instValue.lookupValue("author", reg[1]);
    instValue.lookupValue("price", reg[2]);
	instValue.lookupValue("qty", reg[3]);
	
	const Setting &totValue = root["regType"]["readOnly"]["totValue"];
	totValue.lookupValue("title", reg[4]);
	totValue.lookupValue("author", reg[5]);
    totValue.lookupValue("price", reg[6]);
	totValue.lookupValue("qty", reg[7]);
	std::cout << reg[0] <<  reg[1] << reg[2] << reg[3] << std::endl;
	return reg;
}


std::vector<int> Regconfig::wReg()
{
	const Setting& root = cfg.getRoot();

  // Output a list of all books in the inventory.

    const Setting &readWrite = root["regType"]["readWrite"];
	std::vector<int> reg(10);
	readWrite.lookupValue("title", reg[0]);
	readWrite.lookupValue("author", reg[1]);
    readWrite.lookupValue("price", reg[2]);
	readWrite.lookupValue("qty", reg[3]);
	std::cout << reg[0] <<  reg[1] << reg[2] << reg[3] << std::endl;
	return reg;
}



std::vector<int> Regconfig::alarmReg()
{
	const Setting& root = cfg.getRoot();
    const Setting &readWrite = root["regType"]["alarm"];
	std::vector<int> reg(10);
	readWrite.lookupValue("title", reg[0]);
	readWrite.lookupValue("author", reg[1]);
    readWrite.lookupValue("price", reg[2]);
	readWrite.lookupValue("qty", reg[3]);
	std::cout << reg[0] <<  reg[1] << reg[2] << reg[3] << std::endl;
	return reg;
}


 


