#pragma once
#include <string> 
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
class Log
{
private:
	std::ofstream mLogFile;	
	static Log mLog;
	bool mIsInitialized;
private:
	Log();
	~Log();
	Log(const Log&);
	Log& operator = (const Log&);
	void InternalInitialize(std::string filePath);
	inline bool IsInitialized();
public:
	inline void Info(const std::string& info)
	{
		struct tm *local; 
		time_t t; 
		t=time(NULL); 
		local=localtime(&t);
		std::ostringstream os;
		os<<std::setfill('0')<<std::setw(4)<<local->tm_year + 1900;
		os<<std::setfill('0')<<std::setw(2)<<local->tm_mon + 1;
		os<<std::setfill('0')<<std::setw(2)<<local->tm_mday<<":";
		os<<std::setfill('0')<<std::setw(2)<<local->tm_hour<<":";
		os<<std::setfill('0')<<std::setw(2)<<local->tm_min<<":";
		os<<std::setfill('0')<<std::setw(2)<<local->tm_sec;
		std::cerr<<"["<<os.str()<<"]"<<info<<std::endl;
		mLogFile<<"["<<os.str()<<"]"<<info<<std::endl;
	}	
public:
	static void Initialize(const std::string& filePath);
	inline static Log* Instance()
	{
		if(mLog.IsInitialized())
		{
			return &mLog;
		}
		else
		{
			std::cerr<<"Log is not initialized"<<std::endl;
			exit(0);
		}
	}

};