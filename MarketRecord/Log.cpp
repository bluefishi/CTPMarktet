#include "Log.h"
using namespace std;

Log Log::mLog;
Log::Log()
{
	this->mIsInitialized = false;
}

Log::~Log()
{
	if(mLogFile)
	{
		mLogFile.close();
	}
}

void Log::InternalInitialize(std::string filePath)
{
	mLogFile.open(filePath, ios::app);
	mLogFile<<unitbuf;
	if(!mLogFile)
	{
		std::cerr<<"can not create log file = "<<filePath<<std::endl;
		exit(0);
	}
	mIsInitialized = true;
}

void Log::Initialize(const std::string& filePath)
{
	if(!mLog.IsInitialized())
	{
		mLog.InternalInitialize(filePath);
	}
}

bool Log::IsInitialized()
{
	return mIsInitialized;
}



