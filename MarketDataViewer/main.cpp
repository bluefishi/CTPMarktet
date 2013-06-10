#include <iostream>
#include <fstream>
#include <string>
#include <FormatTransformer.h>
#include <cstdlib>
#include "CTPMarket.CTPTickRecord.pb.h"

using namespace std;
void Usage()
{
	cout<<"MarketDataViewer.exe path2protocol_data path2ouput_dir"<<endl;
}

string GetFileName(const string& path)
{
	int start1 = path.find_last_of('\\');
	int	start2 = path.find_last_of('/');
	return path.substr(max(start1, start2) + 1);
}


int main(int argc, char** argv)
{
	if(argc != 3)		
	{
		Usage();
		return 0;
	}

	ifstream inputFile(argv[1], ios::binary);
	if(!inputFile)
	{
		cerr<<"can not open file = "<<argv[1]<<endl;
		return 0;
	}
	string outputPath = string(argv[2]) +  "\\" + GetFileName(argv[1]) + ".view";
	ofstream outputFile(outputPath.c_str());
	outputFile<<fixed<<scientific;
	CTPMarket::CTPTickRecord cr;
	string stringTickRecord;
	while(!inputFile.eof())
	{
		FormatTransformer::ReadDelimitedProtocol(&cr, &inputFile);
		if(inputFile.eof())
			break;
		FormatTransformer::CTPTickRecordToString(&cr, stringTickRecord);
		outputFile<<stringTickRecord<<endl;
	}
	outputFile.close();
}