// testTraderApi.cpp : 定义控制台应用程序的入口点。
//

#include <windows.h>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "CMdSpi.h"
#include "CTdSpi.h"
#include "CTPConfiguration.h"
#include "..\Common\Protocol\CTPMarket.CTPTickRecord.pb.h"
#include "Log.h"
#include "TimeHelper.h"
#include <string>
#include <iostream>
#include <direct.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
namespace fs = boost::filesystem;
using namespace std;
void Usage(void)
{
	cout<<"MarketRecord.exe path2stroage_dir";
}

void main(int argc, char** argv)
{
	if(argc != 2)
	{
		Usage();
		return;
	}
	//initialize log
	Log::Initialize(TimeHelper::GetDate() + ".log");
	Log::Instance()->Info("Program started");

	//ensure storage rootdir
	CTPConfiguration::Instance()->StorageRootDir = argv[1];
	
	//create stream file directory
	string mdStreamFileDir = fs::current_path().string() + "\\mdapi\\";
	string tdStreamFileDir = fs::current_path().string() + "\\tdapi\\";
	if(!fs::exists(mdStreamFileDir))
	{
		if(!fs::create_directories(mdStreamFileDir))
		{
			Log::Instance()->Info(string("fatal error:") + string("can not create path = ") + mdStreamFileDir); 
			return;
		}
	}

	if(!fs::exists(tdStreamFileDir))
	{
		if(!fs::create_directories(tdStreamFileDir))
		{
			Log::Instance()->Info(string("fatal error:") + string("can not create path = ") + tdStreamFileDir); 
			return;
		}
	}

	// UserApi对象
	CThostFtdcMdApi* pMdUserApi;
	// 初始化UserApi
	pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi(mdStreamFileDir.c_str());// 创建UserApi
	CMdSpi* mdSpiPtr = new CMdSpi(pMdUserApi);
	CThostFtdcMdSpi* pMdUserSpi = mdSpiPtr;
	pMdUserApi->RegisterSpi(pMdUserSpi);						// 注册事件类
	pMdUserApi->RegisterFront(CTPConfiguration::Instance()->FRONT_ADDR);					// connect
	pMdUserApi->Init();

	CThostFtdcTraderApi* pTdUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(tdStreamFileDir.c_str());
	CThostFtdcTraderSpi* pTdUserSpi = new CTdSpi(pTdUserApi, mdSpiPtr);
	pTdUserApi->RegisterSpi(pTdUserSpi);
	pTdUserApi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESUME);
	pTdUserApi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESUME);
	pTdUserApi->RegisterFront(CTPConfiguration::Instance()->FRONT_ADDR);
	pTdUserApi->Init();

	string currentTime;
	while(1)
	{
		currentTime = TimeHelper::GetTime();
		if(currentTime > CTPConfiguration::Instance()->MainThreadExitTime)
		{
			pMdUserApi->RegisterSpi(NULL);
			pMdUserApi->Release();
			pTdUserApi->RegisterSpi(NULL);
			pTdUserApi->Release();
			Log::Instance()->Info("main thread normally exits");
			return;
		}
		else
		{
			Sleep(1000);
		}
	}

//	pUserApi->Join();
//	pUserApi->Release();
}
