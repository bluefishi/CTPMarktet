#include "CTPConfiguration.h"
#include <cstring>
CTPConfiguration::CTPConfiguration()
{
	// 配置参数
	//strcpy(FRONT_ADDR, "tcp://211.136.142.218:9116");		// 前置地址
	strcpy(FRONT_ADDR, "tcp://210.5.151.245:9112");
	//strcpy(BROKER_ID, "1111");				// 经纪公司代码
	strcpy(BROKER_ID, "1111");
	//strcpy(INVESTOR_ID, "Kingnew001");		// 投资者代码
	strcpy(INVESTOR_ID, "kgl010");
	//strcpy(PASSWORD, "888888");
	strcpy(PASSWORD, "888888");
	iRequestID = 0;
	iInstrumentID = 0;
	StorageRootDir = "D:\\Workspaces\\ctp\\data";
	WorkThreadExitTime = "16:00:00";
	MainThreadExitTime = "16:10:00";
}

CTPConfiguration::~CTPConfiguration()
{
}
