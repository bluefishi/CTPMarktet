#include "CTdSpi.h"
#include "Log.h"
#include "TimeHelper.h"
#include "CTPConfiguration.h"
#include <iostream>
#include <Windows.h>
using namespace std;


CTdSpi::CTdSpi(CThostFtdcTraderApi* userApiPtr, CMdSpi* mdSpiPtr)
	:mUserApiPtr(userApiPtr), 
	mConf(CTPConfiguration::Instance()),
	mMdSpiPtr(mdSpiPtr),
	mQueryInstrumentThread(NULL)
{
}


CTdSpi::~CTdSpi(void)
{
	if(mQueryInstrumentThread != NULL)
	{
		delete mQueryInstrumentThread;
	}
}

void CTdSpi::OnFrontConnected()
{
	ostringstream os;
	os << "--->>> " << __FUNCTION__ << endl;
	Log::Instance()->Info(os.str());
	///用户登录请求
	ReqUserLogin();
}

void CTdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, mConf->BROKER_ID);
	strcpy(req.UserID, mConf->INVESTOR_ID);
	strcpy(req.Password, mConf->PASSWORD);
	int iResult = mUserApiPtr->ReqUserLogin(&req, ++(mConf->iRequestID));
	if(iResult == 0)
	{
		Log::Instance()->Info("--->>> 发送用户登录请求: 成功");
	}
	else
	{
		Log::Instance()->Info("--->>> 发送用户登录请求: 失败");
		exit(0);
	}
}

void CTdSpi::OnFrontDisconnected( int nReason )
{
	ostringstream os;
	os << "--->>> " << __FUNCTION__ << endl;
	os << "--->>> Reason = " << nReason << endl;
	Log::Instance()->Info(os.str());
}

void CTdSpi::OnRspUserLogin( CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	ostringstream os;
	os << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		os << "--->>> 获取当前交易日 = " << mUserApiPtr->GetTradingDay() << endl;
		os <<"--->>>TdSpi登录成功";
		Log::Instance()->Info(os.str());
		// 请求订阅行情
		if(mQueryInstrumentThread == NULL)
		{
			mQueryInstrumentThread = new boost::thread(boost::bind(&CTdSpi::QueryInstrumentThread, this));
		}
		
	}
	else
	{
		Log::Instance()->Info("--->>>TdSpi登录失败");
		exit(0);
	}
}

bool CTdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
	{
		ostringstream os;
		os << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
		Log::Instance()->Info(os.str());
	}
	return bResult;
}

void CTdSpi::OnRspQryInstrument( CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	//cout<<__FUNCTION__<<endl;
	//cout<<pInstrument->InstrumentID<<endl;
	mMdSpiPtr->AddSubscribeInstrument(pInstrument->InstrumentID);
}

void CTdSpi::OnHeartBeatWarning( int nTimeLapse )
{
	ostringstream os;
	os << "--->>> " << __FUNCTION__ << endl;
	os << "--->>> nTimerLapse = " << nTimeLapse << endl;
	Log::Instance()->Info(os.str());
}

void CTdSpi::OnRspError( CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	ostringstream os;
	os << "--->>> "<< __FUNCTION__ << endl;
	Log::Instance()->Info(os.str());
	IsErrorRspInfo(pRspInfo);
}

void CTdSpi::QueryInstrumentThread( void )
{
	while(TimeHelper::GetTime() < CTPConfiguration::Instance()->WorkThreadExitTime)
	{
		CThostFtdcQryInstrumentField field;
		memset(&field,0,sizeof(CThostFtdcQryInstrumentField));
		mUserApiPtr->ReqQryInstrument(&field,0);
		Sleep(2000);
	}
}

