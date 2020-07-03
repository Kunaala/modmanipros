#include<iostream>
#define BOOST_CHRONO_VERSION 2
#include<boost/chrono.hpp>
#include<typeinfo>
#include <sstream> 
#include<string>
int main()
{	namespace chrono=boost::chrono;
	//std::cout << chrono::system_clock::now() <<std::endl;//system time
	std::cout << chrono::steady_clock::now() <<std::endl;//time since last boot
  	std::cout << chrono::time_fmt(boost::chrono::timezone::utc, "%D") <<
    chrono::system_clock::now() << '\n';
	std::cout << chrono::time_fmt(boost::chrono::timezone::utc, "%H:%M:%S") <<
    chrono::system_clock::now() << '\n';
	std::stringstream temp;
	temp<<chrono::time_fmt(boost::chrono::timezone::utc, "%H:%M:%S")<<chrono::system_clock::now();
	std::string temp1;
	temp>>temp1;
	std::cout<<temp1;
	return 0;
}
