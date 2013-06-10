#include "MarketDataRecorder.h"
#include "../Common/DataFormat/FormatTransformer.h"
#include "CTPConfiguration.h"
#include "TimeHelper.h"
#include "Log.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <ctime>
namespace fs = boost::filesystem;
using namespace std;
using namespace CTPMarket;

MarketDataRecorder::MarketDataRecorder(void)
{
	Initilize();
	mWriteThread = new boost::thread(boost::bind(&MarketDataRecorder::WriteThread, this));
}


MarketDataRecorder::~MarketDataRecorder(void)
{
	for(auto it = mInstrumentIDFileStreamMap.begin(); it != mInstrumentIDFileStreamMap.end(); ++it)
		it->second->close();
	mLastStand.close();
	delete mWriteThread;
}

void MarketDataRecorder::RecordMarketData( CThostFtdcDepthMarketDataField *pDepthMarketData )
{
	CTPTickRecord* pRec = new CTPTickRecord();
	FormatTransformer::CTPDepthMarketDataFieldToCTPTickRecord(pDepthMarketData, pRec);
	boost::mutex::scoped_lock lock(this->mQueueMutex);
	mQueue.push(pRec);
}

void MarketDataRecorder::Initilize()
{
	//get today
	mToday = TimeHelper::GetDate();

	//ensure diretories
	string todayDir = CTPConfiguration::Instance()->StorageRootDir + "\\" + mToday; 
	if(!fs::exists(todayDir))
	{
		if(!fs::create_directories(todayDir))
		{
			ostringstream os;
			os<<"fatal error:"<<"can not create path = "<<todayDir<<endl;
			Log::Instance()->Info(os.str());
			exit(0);
		}
	}

	//create last stand
	mLastStand.open(todayDir + "\\laststand.ls", ios::binary);
	mLastStand<<unitbuf;
	if(!mLastStand)
	{
		ostringstream os;
		os<<"can not create last stand file = "<<"laststand.ls"<<endl;
		Log::Instance()->Info(os.str());
		exit(0);
	}
}

void MarketDataRecorder::AddInstrument( std::string instrumentID)
{
	string todayDir = CTPConfiguration::Instance()->StorageRootDir + "\\" + mToday; 
	ofstream* of = new ofstream;
	string filePath = todayDir + "\\" + instrumentID + "_" + mToday + ".txt";
	if(!fs::exists(filePath))
	{
		of->open(filePath, ios::binary);
		(*of)<<unitbuf;
		if(!(*of))
		{
			of->close();
			Log::Instance()->Info("use last stand instead of " + instrumentID + ".txt");
			of = &mLastStand;
		}
		mInstrumentIDFileStreamMap[instrumentID] = of;
		return;
	}
	of->open(filePath, ios::app|ios::binary);
	(*of)<<unitbuf;
	if(!(*of))
	{
		of->close();
		Log::Instance()->Info("use last stand instead of " + instrumentID + ".txt");
		of = &mLastStand;
	}
	mInstrumentIDFileStreamMap[instrumentID] = of;
}

void MarketDataRecorder::WriteThread(void)
{
	string currentTime;
	while(true)
	{
		currentTime = TimeHelper::GetTime();
		CTPTickRecord* pTickRecord = NULL;
		if(currentTime < CTPConfiguration::Instance()->WorkThreadExitTime)
		{
			if(!mQueue.empty())
			{
				boost::mutex::scoped_lock lock(this->mQueueMutex);
				if(!mQueue.empty())
				{
					pTickRecord = mQueue.front();
					mQueue.pop();
				}
			}
			if(pTickRecord != NULL)
			{
				if(mInstrumentIDFileStreamMap.find(pTickRecord->instrumentid()) == mInstrumentIDFileStreamMap.end())
				{
					AddInstrument(pTickRecord->instrumentid());
				}
				ofstream* of = mInstrumentIDFileStreamMap[pTickRecord->instrumentid()];
				//pTickRecord->SerializeToOstream(of);
				FormatTransformer::WriteDelimitedProtocol(pTickRecord, of);
				of->flush();
				delete pTickRecord;
			}
		}
		else
		{
			boost::mutex::scoped_lock lock(this->mQueueMutex);
			while(!mQueue.empty())
			{
				pTickRecord = mQueue.front();
				mQueue.pop();
				if(mInstrumentIDFileStreamMap.find(pTickRecord->instrumentid()) == mInstrumentIDFileStreamMap.end())
				{
					AddInstrument(pTickRecord->instrumentid());
				}
				ofstream* of = mInstrumentIDFileStreamMap[pTickRecord->instrumentid()];
				//pTickRecord->SerializeToOstream(of);
				FormatTransformer::WriteDelimitedProtocol(pTickRecord, of);
				delete pTickRecord;
			}
			break;
		}
	}
	ostringstream os;
	os<<__FUNCTION__<<"normally exits"<<endl;
	Log::Instance()->Info(os.str());
}
