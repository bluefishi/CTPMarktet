#pragma once
#include "ThostFtdcMdApi.h"
#include "../Protocol/CTPMarket.CTPTickRecord.pb.h"
#include <string>
#include <sstream>
#include <fstream>
class FormatTransformer
{
public:
	static void CTPDepthMarketDataFieldToSTring(CThostFtdcDepthMarketDataField* pDepthMarketData, std::string& result);

	static void CTPTickRecordToString(CTPMarket::CTPTickRecord* pTickRecord, std::string& result);

	static void CTPTickRecordToCTPDepthMarketDataField(CTPMarket::CTPTickRecord* pTickRecord, CThostFtdcDepthMarketDataField* pDepthMarketData);

	static void CTPDepthMarketDataFieldToCTPTickRecord(CThostFtdcDepthMarketDataField* pDepthMarketData, CTPMarket::CTPTickRecord* pTickRecord);

	static bool WriteDelimitedProtocol(CTPMarket::CTPTickRecord* pTickRecord, std::ofstream* fp);
	
	static bool ReadDelimitedProtocol(CTPMarket::CTPTickRecord* pTickRecord, std::ifstream* fp);
};