#pragma once
#include<vector>
#include<string>
#include"Data_Mem.h"
#include"processor.h"
#include<future>
#include<ctime>
class nSIM 
{
public:
	nSIM (int, std::vector<std::string>&);
	void execute_all(std::vector<Data_Mem>::pointer);
	~nSIM ();

private:
	std::vector<std::string> paths;
	void create_sims();
	void execute_one(int, std::vector<Data_Mem>::pointer);
	std::vector<processor> SIM;
	int n;
};

nSIM::nSIM (int n, std::vector<std::string>& ps)
	:n(n), paths(ps) {
	create_sims();
}
void nSIM::create_sims() {
	for (int i = 0; i < n; i++) {
		processor p;
		SIM.push_back(p);
	}
}
void nSIM::execute_all(std::vector<Data_Mem>::pointer data_mem) {
	for (int i = 0; i < n; i++) {
		execute_one(i, data_mem);
	}
}
void nSIM::execute_one(int index, std::vector<Data_Mem>::pointer data_mem) {
	auto res = std::async(std::launch::async, SIM[index], paths[index], data_mem);
}
nSIM ::~nSIM (){}
