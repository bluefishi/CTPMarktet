#include "TimeHelper.h"
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;
TimeHelper::TimeHelper(void)
{
}


TimeHelper::~TimeHelper(void)
{
}

std::string TimeHelper::GetDate()
{
	struct tm *local; 
	time_t t; 
	t=time(NULL); 
	local=localtime(&t);
	ostringstream os;
	os<<setfill('0')<<setw(4)<<local->tm_year + 1900;
	os<<setfill('0')<<setw(2)<<local->tm_mon + 1;
	os<<setfill('0')<<setw(2)<<local->tm_mday;
	return os.str();
}

std::string TimeHelper::GetTime()
{
	struct tm *local; 
	time_t t; 
	ostringstream os;
	t=time(NULL); 
	local=localtime(&t);
	os.clear();
	os.str("");
	os<<setfill('0')<<setw(2)<<local->tm_hour<<":";
	os<<setfill('0')<<setw(2)<<local->tm_min<<":";
	os<<setfill('0')<<setw(2)<<local->tm_sec;
	return os.str();
}
