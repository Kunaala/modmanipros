#include<iostream>
#define BOOST_CHRONO_VERSION 2
#include<boost/chrono.hpp>
#include <sstream> 
#include<string>
//#include<typeinfo>
int main()
{	namespace chrono=boost::chrono;
	//std::cout << chrono::steady_clock::now() <<std::endl;		//time since last boot
  	//std::cout << chrono::time_fmt(boost::chrono::timezone::utc, "%D") << chrono::system_clock::now() << '\n';
	//std::cout << chrono::time_fmt(boost::chrono::timezone::utc, "%H:%M:%S") << chrono::system_clock::now() << '\n';
	std::stringstream temp1,temp2;
	std::string datestr,timestr;
	temp1<<chrono::time_fmt(boost::chrono::timezone::utc, "%H:%M:%S")<<chrono::system_clock::now();
	temp2<<chrono::time_fmt(boost::chrono::timezone::utc, "%D") << chrono::system_clock::now();
	temp1>>datestr;
	temp2>>timestr;
	std::cout<<datestr<<":"<<timestr;
	return 0;
}
