#include <iostream>
#include "iniparser.hpp"

int main(int argc, char** argv)
{
	int ival;
	INI::Array dval;
	// Creating ini file object
	INI::File ft;
	// Loading from file
	if (!ft.Load("joker.ini"))
	{
		// Loading from stream
		// std::ifstream op("opts.ini",std::ios::in);
		// if (op.is_open())
		// 	op >> ft;
        std::cout<<"error opening file"<<std::endl;

	}
    ival = ft.GetSection("bga")->GetValue("id",0).AsInt();
    dval = ft.GetSection("bga")->GetValue("checha").AsArray();
    std::cout<<dval.Size()<<std::endl;
    return 0;
}