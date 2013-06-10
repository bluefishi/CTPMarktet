#pragma once
#include <ThostFtdcMdApi.h>
#include <string>
class CTPConfiguration
{
private:
	CTPConfiguration();
	~CTPConfiguration();
	CTPConfiguration(const CTPConfiguration&);
	CTPConfiguration& operator = (const CTPConfiguration&);
public:
	char FRONT_ADDR[50];
	TThostFtdcBrokerIDType BROKER_ID;
	TThostFtdcInvestorIDType INVESTOR_ID;
	char* ppInstrumentID[1024];
	int iInstrumentID;
	TThostFtdcPasswordType  PASSWORD;
	int iRequestID;
	std::string StorageRootDir;
	std::string WorkThreadExitTime;
	std::string MainThreadExitTime;
public:
	inline static CTPConfiguration* Instance()
	{
		static CTPConfiguration instance;
		return &instance;
	}
};