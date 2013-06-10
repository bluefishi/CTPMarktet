#pragma once
#include "ThostFtdcMdApi.h"
#include <cstring>
class CTPTickRecord
{
public:
	///交易日
	char TradingDay[9];
	///合约代码
	char InstrumentID[31];
	///交易所代码
	char ExchangeID[9];
	///合约在交易所的代码
	char ExchangeInstID[31];
	///最新价
	double	LastPrice;
	///上次结算价
	double	PreSettlementPrice;
	///昨收盘
	double PreClosePrice;
	///昨持仓量
	double PreOpenInterest;
	///今开盘
	double OpenPrice;
	///最高价
	double HighestPrice;
	///最低价
	double LowestPrice;
	///数量
	int Volume;
	///成交金额
	double Turnover;
	///持仓量
	double OpenInterest;
	///今收盘
	double ClosePrice;
	///本次结算价
	double SettlementPrice;
	///涨停板价
	double UpperLimitPrice;
	///跌停板价
	double LowerLimitPrice;
	///昨虚实度
	double PreDelta;
	///今虚实度
	double CurrDelta;
	///最后修改时间
	char UpdateTime[9];
	///最后修改毫秒
	int UpdateMillisec;
	///申买价一
	double BidPrice1;
	///申买量一
	int	BidVolume1;
	///申卖价一
	double	AskPrice1;
	///申卖量一
	int	AskVolume1;
	///申买价二
	double BidPrice2;
	///申买量二
	int	BidVolume2;
	///申卖价二
	double	AskPrice2;
	///申卖量二
	int	AskVolume2;
	///申买价三
	double	BidPrice3;
	///申买量三
	int	BidVolume3;
	///申卖价三
	double	AskPrice3;
	///申卖量三
	int	AskVolume3;
	///申买价四
	double	BidPrice4;
	///申买量四
	int	BidVolume4;
	///申卖价四
	double	AskPrice4;
	///申卖量四
	int	AskVolume4;
	///申买价五
	double	BidPrice5;
	///申买量五
	int	BidVolume5;
	///申卖价五
	double	AskPrice5;
	///申卖量五
	int	AskVolume5;
	///当日均价
	double	AveragePrice;
public:
	CTPTickRecord(CThostFtdcDepthMarketDataField* pMarketData)
	{
		strncpy(this->TradingDay, pMarketData->TradingDay, 9);
		strncpy(this->InstrumentID, pMarketData->InstrumentID, 31);
		strncpy(this->ExchangeID, pMarketData->ExchangeID, 9);
		strncpy(this->ExchangeInstID, pMarketData->ExchangeInstID, 31);
		this->LastPrice = pMarketData->LastPrice;
		this->PreSettlementPrice = pMarketData->PreSettlementPrice;
		this->PreClosePrice = pMarketData->PreClosePrice;
		this->PreOpenInterest = pMarketData->PreOpenInterest;
		this->OpenPrice = pMarketData->OpenPrice;
		this->HighestPrice = pMarketData->HighestPrice;
		this->LowestPrice = pMarketData->LowestPrice;
		this->Volume = pMarketData->Volume;
		this->Turnover = pMarketData->Turnover;
		this->OpenInterest = pMarketData->OpenInterest;
		this->ClosePrice = pMarketData->ClosePrice;
		this->SettlementPrice = pMarketData->SettlementPrice;
		this->UpperLimitPrice = pMarketData->UpperLimitPrice;
		this->LowerLimitPrice = pMarketData->LowerLimitPrice;
		this->PreDelta = pMarketData->PreDelta;
		this->CurrDelta = pMarketData->CurrDelta;
		strncpy(this->UpdateTime, pMarketData->UpdateTime, 9);
		this->UpdateMillisec = pMarketData->UpdateMillisec;
		this->BidPrice1 = pMarketData->BidPrice1;
		this->BidVolume1 = pMarketData->BidVolume1;
		this->AskPrice1 = pMarketData->AskPrice1;
		this->AskVolume1 = pMarketData->AskVolume1;
		this->BidPrice2 = pMarketData->BidPrice2;
		this->BidVolume2 = pMarketData->BidVolume2;
		this->AskPrice2 = pMarketData->AskPrice2;
		this->AskVolume2 = pMarketData->AskVolume2;
		this->BidPrice3 = pMarketData->BidPrice3;
		this->BidVolume3 = pMarketData->BidVolume3;
		this->AskPrice3 = pMarketData->AskPrice3;
		this->AskVolume3 = pMarketData->AskVolume3;
		this->BidPrice4 = pMarketData->BidPrice4;
		this->BidVolume4 = pMarketData->BidVolume4;
		this->AskPrice4 = pMarketData->AskPrice4;
		this->AskVolume4 = pMarketData->AskVolume4;
		this->BidPrice5 = pMarketData->BidPrice5;
		this->BidVolume5 = pMarketData->BidVolume5;
		this->AskPrice5 = pMarketData->AskPrice5;
		this->AskVolume5 = pMarketData->AskVolume5;
		this->AveragePrice = pMarketData->AveragePrice;
	}
};