#include "FormatTransformer.h"
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <Winsock2.h>
#include <iostream>
using namespace std;
using namespace google::protobuf::io;

void FormatTransformer::CTPDepthMarketDataFieldToSTring(CThostFtdcDepthMarketDataField* pDepthMarketData, std::string& result)
{
	std::ostringstream os;
	os<<std::fixed;
	os<<pDepthMarketData->TradingDay<<",";
	os<<pDepthMarketData->UpdateTime<<",";
	os<<pDepthMarketData->UpdateMillisec<<",";
	os<<pDepthMarketData->InstrumentID<<",";
	os<<pDepthMarketData->ExchangeID<<",";
	os<<pDepthMarketData->ExchangeInstID<<",";
	os<<pDepthMarketData->LastPrice<<",";
	os<<pDepthMarketData->PreSettlementPrice<<",";
	os<<pDepthMarketData->PreClosePrice<<",";
	os<<pDepthMarketData->PreOpenInterest<<",";
	os<<pDepthMarketData->OpenPrice<<",";
	os<<pDepthMarketData->HighestPrice<<",";
	os<<pDepthMarketData->LowestPrice<<",";
	os<<pDepthMarketData->Volume<<",";
	os<<pDepthMarketData->Turnover<<",";
	os<<pDepthMarketData->OpenInterest<<",";
	os<<pDepthMarketData->ClosePrice<<",";
	os<<pDepthMarketData->SettlementPrice<<",";
	os<<pDepthMarketData->UpperLimitPrice<<",";
	os<<pDepthMarketData->LowerLimitPrice<<",";
	os<<pDepthMarketData->PreDelta<<",";
	os<<pDepthMarketData->CurrDelta<<",";
	os<<pDepthMarketData->BidPrice1<<",";
	os<<pDepthMarketData->BidVolume1<<",";
	os<<pDepthMarketData->AskPrice1<<",";
	os<<pDepthMarketData->AskVolume1<<",";
	os<<pDepthMarketData->BidPrice2<<",";
	os<<pDepthMarketData->BidVolume2<<",";
	os<<pDepthMarketData->AskPrice2<<",";
	os<<pDepthMarketData->AskVolume2<<",";
	os<<pDepthMarketData->BidPrice3<<",";
	os<<pDepthMarketData->BidVolume3<<",";
	os<<pDepthMarketData->AskPrice3<<",";
	os<<pDepthMarketData->AskVolume3<<",";
	os<<pDepthMarketData->BidPrice4<<",";
	os<<pDepthMarketData->BidVolume4<<",";
	os<<pDepthMarketData->AskPrice4<<",";
	os<<pDepthMarketData->AskVolume4<<",";
	os<<pDepthMarketData->BidPrice5<<",";
	os<<pDepthMarketData->BidVolume5<<",";
	os<<pDepthMarketData->AskPrice5<<",";
	os<<pDepthMarketData->AskVolume5<<",";
	os<<pDepthMarketData->AveragePrice<<std::endl;
	result = os.str();
}

void FormatTransformer::CTPTickRecordToString(CTPMarket::CTPTickRecord* pTickRecord, std::string& result)
{
	std::ostringstream os;
	os<<pTickRecord->tradingday()<<",";
	os<<pTickRecord->updatetime()<<",";
	os<<pTickRecord->updatemillisec()<<",";
	os<<pTickRecord->instrumentid()<<",";
	os<<pTickRecord->exchangeid()<<",";
	os<<pTickRecord->exchangeinstid()<<",";
	os<<pTickRecord->lastprice()<<",";
	os<<pTickRecord->presettlementprice()<<",";
	os<<pTickRecord->precloseprice()<<",";
	os<<pTickRecord->preopeninterest()<<",";
	os<<pTickRecord->openprice()<<",";
	os<<pTickRecord->highestprice()<<",";
	os<<pTickRecord->lowestprice()<<",";
	os<<pTickRecord->volume()<<",";
	os<<pTickRecord->turnover()<<",";
	os<<pTickRecord->openinterest()<<",";
	os<<pTickRecord->closeprice()<<",";
	os<<pTickRecord->settlementprice()<<",";
	os<<pTickRecord->upperlimitprice()<<",";
	os<<pTickRecord->lowerlimitprice()<<",";
	os<<pTickRecord->predelta()<<",";
	os<<pTickRecord->currdelta()<<",";
	os<<pTickRecord->bidprice1()<<",";
	os<<pTickRecord->bidvolume1()<<",";
	os<<pTickRecord->askprice1()<<",";
	os<<pTickRecord->askvolume1()<<",";
	os<<pTickRecord->bidprice2()<<",";
	os<<pTickRecord->bidvolume2()<<",";
	os<<pTickRecord->askprice2()<<",";
	os<<pTickRecord->askvolume2()<<",";
	os<<pTickRecord->bidprice3()<<",";
	os<<pTickRecord->bidvolume3()<<",";
	os<<pTickRecord->askprice3()<<",";
	os<<pTickRecord->askvolume3()<<",";
	os<<pTickRecord->bidprice4()<<",";
	os<<pTickRecord->bidvolume4()<<",";
	os<<pTickRecord->askprice4()<<",";
	os<<pTickRecord->askvolume4()<<",";
	os<<pTickRecord->bidprice5()<<",";
	os<<pTickRecord->bidvolume5()<<",";
	os<<pTickRecord->askprice5()<<",";
	os<<pTickRecord->askvolume5()<<",";
	os<<pTickRecord->averageprice();
	result = os.str();
}

void FormatTransformer::CTPTickRecordToCTPDepthMarketDataField(CTPMarket::CTPTickRecord* pTickRecord, CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	strncpy(pDepthMarketData->TradingDay, pTickRecord->tradingday().c_str(), 9);
	strncpy(pDepthMarketData->InstrumentID, pTickRecord->instrumentid().c_str(), 31);
	strncpy(pDepthMarketData->ExchangeID, pTickRecord->exchangeid().c_str(), 9);
	strncpy(pDepthMarketData->ExchangeInstID, pTickRecord->exchangeinstid().c_str(), 31);
	pDepthMarketData->LastPrice = pTickRecord->lastprice();
	pDepthMarketData->PreSettlementPrice = pTickRecord->presettlementprice();
	pDepthMarketData->PreClosePrice = pTickRecord->precloseprice();
	pDepthMarketData->PreOpenInterest = pTickRecord->preopeninterest();
	pDepthMarketData->OpenPrice = pTickRecord->openprice();
	pDepthMarketData->HighestPrice = pTickRecord->highestprice();
	pDepthMarketData->LowestPrice = pTickRecord->lowestprice();
	pDepthMarketData->Volume = pTickRecord->volume();
	pDepthMarketData->Turnover = pTickRecord->turnover();
	pDepthMarketData->OpenInterest = pTickRecord->openinterest();
	pDepthMarketData->ClosePrice = pTickRecord->closeprice();
	pDepthMarketData->SettlementPrice = pTickRecord->settlementprice();
	pDepthMarketData->UpperLimitPrice = pTickRecord->upperlimitprice();
	pDepthMarketData->LowerLimitPrice = pTickRecord->lowerlimitprice();
	pDepthMarketData->PreDelta = pTickRecord->predelta();
	pDepthMarketData->CurrDelta = pTickRecord->currdelta();
	strncpy(pDepthMarketData->UpdateTime, pTickRecord->updatetime().c_str(), 9);
	pDepthMarketData->UpdateMillisec = pTickRecord->updatemillisec();
	pDepthMarketData->BidPrice1 = pTickRecord->bidprice1();
	pDepthMarketData->BidVolume1 = pTickRecord->bidvolume1();
	pDepthMarketData->AskPrice1 = pTickRecord->askprice1();
	pDepthMarketData->AskVolume1 = pTickRecord->askvolume1();
	pDepthMarketData->BidPrice2 = pTickRecord->bidprice2();
	pDepthMarketData->BidVolume2 = pTickRecord->bidvolume2();
	pDepthMarketData->AskPrice2 = pTickRecord->askprice2();
	pDepthMarketData->AskVolume2 = pTickRecord->askvolume2();
	pDepthMarketData->BidPrice3 = pTickRecord->bidprice3();
	pDepthMarketData->BidVolume3 = pTickRecord->bidvolume3();
	pDepthMarketData->AskPrice3 = pTickRecord->askprice3();
	pDepthMarketData->AskVolume3 = pTickRecord->askvolume3();
	pDepthMarketData->BidPrice4 = pTickRecord->bidprice4();
	pDepthMarketData->BidVolume4 = pTickRecord->bidvolume4();
	pDepthMarketData->AskPrice4 = pTickRecord->askprice4();
	pDepthMarketData->AskVolume4 = pTickRecord->askvolume4();
	pDepthMarketData->BidPrice5 = pTickRecord->bidprice5();
	pDepthMarketData->BidVolume5 = pTickRecord->bidvolume5();
	pDepthMarketData->AskPrice5 = pTickRecord->askprice5();
	pDepthMarketData->AskVolume5 = pTickRecord->askvolume5();
	pDepthMarketData->AveragePrice = pTickRecord->averageprice();
}

void FormatTransformer::CTPDepthMarketDataFieldToCTPTickRecord(CThostFtdcDepthMarketDataField* pDepthMarketData, CTPMarket::CTPTickRecord* pTickRecord)
{
	pTickRecord->set_tradingday(pDepthMarketData->TradingDay);
	pTickRecord->set_instrumentid(pDepthMarketData->InstrumentID);
	pTickRecord->set_exchangeid(pDepthMarketData->ExchangeID);
	pTickRecord->set_exchangeinstid(pDepthMarketData->ExchangeInstID);
	pTickRecord->set_lastprice(pDepthMarketData->LastPrice);
	pTickRecord->set_presettlementprice(pDepthMarketData->PreSettlementPrice);
	pTickRecord->set_precloseprice(pDepthMarketData->PreClosePrice);
	pTickRecord->set_preopeninterest(pDepthMarketData->PreOpenInterest);
	pTickRecord->set_openprice(pDepthMarketData->OpenPrice);
	pTickRecord->set_highestprice(pDepthMarketData->HighestPrice);
	pTickRecord->set_lowestprice(pDepthMarketData->LowestPrice);
	pTickRecord->set_volume(pDepthMarketData->Volume);
	pTickRecord->set_turnover(pDepthMarketData->Turnover);
	pTickRecord->set_openinterest(pDepthMarketData->OpenInterest);
	pTickRecord->set_closeprice(pDepthMarketData->ClosePrice);
	pTickRecord->set_settlementprice(pDepthMarketData->SettlementPrice);
	pTickRecord->set_upperlimitprice(pDepthMarketData->UpperLimitPrice);
	pTickRecord->set_lowerlimitprice(pDepthMarketData->LowerLimitPrice);
	pTickRecord->set_predelta(pDepthMarketData->PreDelta);
	pTickRecord->set_currdelta(pDepthMarketData->CurrDelta);
	pTickRecord->set_updatetime(pDepthMarketData->UpdateTime);
	pTickRecord->set_updatemillisec(pDepthMarketData->UpdateMillisec);
	pTickRecord->set_bidprice1(pDepthMarketData->BidPrice1);
	pTickRecord->set_bidvolume1(pDepthMarketData->BidVolume1);
	pTickRecord->set_askprice1(pDepthMarketData->AskPrice1);
	pTickRecord->set_askvolume1(pDepthMarketData->AskVolume1);
	pTickRecord->set_bidprice2(pDepthMarketData->BidPrice2);
	pTickRecord->set_bidvolume2(pDepthMarketData->BidVolume2);
	pTickRecord->set_askprice2(pDepthMarketData->AskPrice2);
	pTickRecord->set_askvolume2(pDepthMarketData->AskVolume2);
	pTickRecord->set_bidprice3(pDepthMarketData->BidPrice3);
	pTickRecord->set_bidvolume3(pDepthMarketData->BidVolume3);
	pTickRecord->set_askprice3(pDepthMarketData->AskPrice3);
	pTickRecord->set_askvolume3(pDepthMarketData->AskVolume3);
	pTickRecord->set_bidprice4(pDepthMarketData->BidPrice4);
	pTickRecord->set_bidvolume4(pDepthMarketData->BidVolume4);
	pTickRecord->set_askprice4(pDepthMarketData->AskPrice4);
	pTickRecord->set_askvolume4(pDepthMarketData->AskVolume4);
	pTickRecord->set_bidprice5(pDepthMarketData->BidPrice5);
	pTickRecord->set_bidvolume5(pDepthMarketData->BidVolume5);
	pTickRecord->set_askprice5(pDepthMarketData->AskPrice5);
	pTickRecord->set_askvolume5(pDepthMarketData->AskVolume5);
	pTickRecord->set_averageprice(pDepthMarketData->AveragePrice);	
}

bool FormatTransformer::WriteDelimitedProtocol( CTPMarket::CTPTickRecord* pTickRecord, std::ofstream* fp )
{
	static char* buffer= new char[1024 * 512];
	google::protobuf::uint32 size = pTickRecord->ByteSize();
	google::protobuf::uint32 nsize;
	nsize = htonl(size);
	fp->write(reinterpret_cast<char*>(&nsize), sizeof(nsize));
	bool ret = pTickRecord->SerializeToArray(buffer, size);
	fp->write(buffer, size);
	return ret;
}

bool FormatTransformer::ReadDelimitedProtocol( CTPMarket::CTPTickRecord* pTickRecord, std::ifstream* fp )
{
	static char* buffer = new char[1024 * 512];
	google::protobuf::uint32 size;
	google::protobuf::uint32 nsize;
	fp->read(reinterpret_cast<char*>(&nsize), sizeof(nsize));
	if(fp->eof())
		return false;
	size = ntohl(nsize);
	fp->read(buffer, size);
	if(fp->eof())
		return false;
	return pTickRecord->ParseFromArray(buffer, size);
}
