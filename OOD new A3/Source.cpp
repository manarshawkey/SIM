#include<iostream>
#include<string>
#include<vector>
#include"processor.h"
#include"Data_Mem.h"
#include"nSIM.h"
using namespace std;
/*
ASS -32 @222
WRITE @222
NEG @2 @3
WRITE @3
LE @3 -2 @44
WRITE 44
*/
int main() {
	vector<Data_Mem> data_mem(1024);
	std::string path = "input.txt";
	std::vector<std::string> paths;
	paths.push_back(path);
	paths.push_back(path);
	nSIM simulators(2, paths);
	vector<Data_Mem>::pointer d;
	d = &data_mem[0];
	simulators.execute_all(d);
	return 0;
}