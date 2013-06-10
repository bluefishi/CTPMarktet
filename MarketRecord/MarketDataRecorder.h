#pragma once
#include<string>
#include<map>
#include<fstream>
#include "ThostFtdcMdApi.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <queue>
#include "../Common/Protocol/CTPMarket.CTPTickRecord.pb.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
class MarketDataRecorder
{
private:
	std::map<std::string, std::ofstream*> mInstrumentIDFileStreamMap;
	std::queue<CTPMarket::CTPTickRecord*> mQueue;
	boost::mutex mQueueMutex;
	std::string mToday;
	std::ofstream mLastStand;
	boost::thread* mWriteThread;
private:
	void Initilize();
	void AddInstrument(std::string instrumentID);
	void WriteThread(void);
public:
	MarketDataRecorder(void);
	~MarketDataRecorder(void);
public:
	void RecordMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

};

