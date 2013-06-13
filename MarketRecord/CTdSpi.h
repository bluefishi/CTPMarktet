#pragma once
#include "CTPConfiguration.h"
#include "CMdSpi.h"
#include "ThostFtdcTraderApi.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
class CTdSpi :
	public CThostFtdcTraderSpi
{
private:
	CTPConfiguration* mConf;
	CThostFtdcTraderApi* mUserApiPtr;
	CMdSpi* mMdSpiPtr;
public:
	CTdSpi(CThostFtdcTraderApi *pUserApi, CMdSpi* mdSpiPtr);
	virtual ~CTdSpi(void);
public:
	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast);
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse);
	// 当客户端与交易托管系统建立起通信连接，客户端需要进行登录
	virtual void OnFrontConnected();
	// 当客户端与交易托管系统通信连接断开时，该方法被调用
	virtual void OnFrontDisconnected(int nReason);
	// 当客户端发出登录请求之后，该方法会被调用，通知客户端登录是否成功
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField
		*pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool
		bIsLast);
	//请求合约信息应答
	virtual void OnRspQryInstrument(
		CThostFtdcInstrumentField *pInstrument,
		CThostFtdcRspInfoField *pRspInfo,
		int nRequestID,
		bool bIsLast); 

private:
	void ReqUserLogin();
	bool CTdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
	void QueryInstrumentThread(void);
};

