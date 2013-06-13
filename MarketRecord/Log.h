#pragma once
#include <string> 
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "TimeHelper.h"
class Log
{
private:
	std::ofstream mLogFile;	
	static Log mLog;
	bool mIsInitialized;
	boost::mutex mLogMutex;
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
		os<<TimeHelper::GetDate()<<":"<<TimeHelper::GetTime();
		std::cerr<<"["<<os.str()<<"]"<<info<<std::endl;
		boost::mutex::scoped_lock lock(mLogMutex);
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