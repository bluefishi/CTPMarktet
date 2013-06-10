#pragma once
#include <string>
class TimeHelper
{
public:
	static std::string GetDate();
	static std::string GetTime();
public:
	TimeHelper(void);
	~TimeHelper(void);
};

