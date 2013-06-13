#include "CMdSpi.h"
#include <iostream>
#include "Log.h"
#include "CTPConfiguration.h"
#include "TimeHelper.h"
#include <cstring>
#include <string>
#include <Windows.h>
#include <sstream>
using namespace std;

#pragma warning(disable : 4996)

// USER_API参数
//extern CThostFtdcMdApi* pUserApi;

// 配置参数
//extern char FRONT_ADDR[];		
//extern TThostFtdcBrokerIDType	BROKER_ID;
//extern TThostFtdcInvestorIDType INVESTOR_ID;
//extern TThostFtdcPasswordType	PASSWORD;
//extern char* ppInstrumentID[];	
//extern int iInstrumentID;

// 请求编号
//extern int iRequestID;

void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast)
{
	//cerr << "--->>> "<< __FUNCTION__ << endl;
	Log::Instance()->Info(__FUNCTION__);
	IsErrorRspInfo(pRspInfo);
}

void CMdSpi::OnFrontDisconnected(int nReason)
{
	ostringstream os;
	os<< "--->>> " <<__FUNCTION__ << endl;
	os<< "--->>> Reason = " << nReason << endl;
	Log::Instance()->Info(os.str());
}
		
void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	ostringstream os;
	os << "--->>> " <<__FUNCTION__ << endl;
	os << "--->>> nTimerLapse = " << nTimeLapse << endl;
	Log::Instance()->Info(os.str());
}

void CMdSpi::OnFrontConnected()
{
	ostringstream os;
	os << "--->>> " << __FUNCTION__ << endl;
	Log::Instance()->Info(os.str());
	///用户登录请求
	ReqUserLogin();
}

void CMdSpi::ReqUserLogin()
{
	static int iRequestID = 0;
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, mConf->BROKER_ID);
	strcpy(req.UserID, mConf->INVESTOR_ID);
	strcpy(req.Password, mConf->PASSWORD);
	int iResult = mUserApiPtr->ReqUserLogin(&req, ++iRequestID);
	if(iResult == 0)
	{
		Log::Instance()->Info("--->>>CMdSpi 发送用户登录请求: 成功");
	}
	else
	{
		Log::Instance()->Info("--->>>CMdSpi 发送用户登录请求: 失败");
		exit(0);
	}
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	ostringstream os;
	os << "--->>> " <<__FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		os << "--->>>CMdSpi 获取当前交易日 = " << mUserApiPtr->GetTradingDay() << endl;
		os <<"--->>>CMdSpi登录成功"<<endl;
		Log::Instance()->Info(os.str());
		// 请求订阅行情
		//SubscribeMarketData();	
		if(mSubscribeInstrumentThread == NULL)
		{			
			//first connect
			mSubscribeInstrumentThread = new boost::thread(boost::bind(&CMdSpi::SuscribeInstrumentThread, this));
		}
		else
		{
			//re connect
			boost::mutex::scoped_lock lock(this->mQueueMutex);
			for(auto it = mSubscribedInstrumentSet.begin(); it != mSubscribedInstrumentSet.end(); ++it)
			{
				mSubscribeQueue.push(*it);
			}

		}
	}
	else
	{
		Log::Instance()->Info("--->>>CMdSpi登录失败");
		exit(0);
	}
}

void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << __FUNCTION__ << endl;
}

void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << __FUNCTION__ << endl;
}

void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//在这里记录数据
	//cerr << __FUNCTION__ << endl;
	//cout<<pDepthMarketData->InstrumentID<<endl;
	mRecorder.RecordMarketData(pDepthMarketData);
}

bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	ostringstream os;
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
	{
		os << "--->>>CMdSpi:: ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
		Log::Instance()->Info(os.str());
	}
	return bResult;
}

void CMdSpi::AddSubscribeInstrument( char* instrumentID )
{
	boost::mutex::scoped_lock lock(this->mQueueMutex);
	if(mSubscribedInstrumentSet.count(instrumentID) == 0)
	{
		mSubscribeQueue.push(instrumentID);
		mSubscribedInstrumentSet.insert(instrumentID);
	}

}

void CMdSpi::SuscribeInstrumentThread( void )
{
	int batch = 20;
	int index = 0;
	char** ppInstrumentID = new char* [batch];
	for(int i = 0; i < batch; ++i)
	{
		ppInstrumentID[i] = new char[50];
	}
	while(TimeHelper::GetTime() < CTPConfiguration::Instance()->WorkThreadExitTime)
	{
		index = 0;
		if(!mSubscribeQueue.empty())
		{
			boost::mutex::scoped_lock lock(this->mQueueMutex);
			while(!mSubscribeQueue.empty() && index < batch)
			{
				strncpy(ppInstrumentID[index], mSubscribeQueue.front().c_str(), 50);
				mSubscribeQueue.pop();
				++index;
			}
		}
		if(index != 0)
		{
			for(int i = 0; i < index; ++i)
			{
				Log::Instance()->Info(string("subscribe ") + ppInstrumentID[i]);
			}
			int iResult = mUserApiPtr->SubscribeMarketData(ppInstrumentID, index); 
			if(iResult != 0)
			{
				Log::Instance()->Info(string("--->>>订阅行情 ") + " 失败");
				boost::mutex::scoped_lock lock(this->mQueueMutex);
				for(int i = 0; i < index; ++i)
				{
					mSubscribedInstrumentSet.erase(ppInstrumentID[i]);
				}
			}
		}
		Sleep(10);
	}
	ostringstream os;
	os<<__FUNCTION__<<"normally exits"<<endl;
	Log::Instance()->Info(os.str());
	for(int i = 0; i < batch; ++i)
	{
		delete[] ppInstrumentID[i];
	}
	delete[] ppInstrumentID;
}
