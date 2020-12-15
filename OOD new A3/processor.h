#pragma once
#include<iostream>
#include<string>
#include"InstFactory.h"
#include<vector>
#include"Data_Mem.h"
class processor {
public:
	processor();
	void execute_program(std::string, std::vector<Data_Mem>::pointer);
	void operator()(std::string, std::vector<Data_Mem>::pointer); 
private:
	InstFactory factory;
	void parse(std::string, std::vector<Data_Mem>::pointer);
	std::vector<instruction*> inst_mem;
};
void processor::operator()(std::string p, std::vector<Data_Mem>::pointer d){execute_program(p, d);}
processor::processor(){}
void processor::execute_program(std::string file_path, std::vector<Data_Mem>::pointer data_mem) {
	try {
		parse(file_path, data_mem);
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	bool halt = 0;
	int res;
	try {
		for (int pc = 0; pc < inst_mem.size(); pc++) {
			try{
				res = inst_mem[pc]->execute();
			}
			catch (const std::exception & e){
				std::cout << "Error reported while program execution: " << e.what() << std::endl;
			}
			if (res == 0)
				continue;
			if (res == -1) {
				halt = 1;
				break;
			}
			else
				pc = res - 1;
		}
		if (!halt)
			throw std::exception("no halt command to terminate the execution!\n");
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}
void processor::parse(std::string path, std::vector<Data_Mem>::pointer data_mem) {
	factory.parse(path, inst_mem, data_mem);
}
