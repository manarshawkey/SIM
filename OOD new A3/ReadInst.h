#pragma once
#include<iostream>
#include<string>
#include<stdexcept>
#include"instruction.h"
#include"Data_Mem.h"
//#include"globals.h"
class ReadInst : public instruction {
public:
	ReadInst(int, std::vector<Data_Mem>::pointer);
	virtual int execute();
	~ReadInst();
private:
	int address;
	std::vector<Data_Mem>::pointer data_mem;
};
ReadInst::ReadInst(int addr, std::vector<Data_Mem>::pointer data)
	:data_mem(&data[0]), 
	address((addr <= 0 || addr > 1023) ? throw std::invalid_argument("Invalid mem location.\n") : addr) {}
int ReadInst::execute() {
	int value;
	std::cout << "Read executes: please enter a value: ";
	std::cin >> value;
	data_mem[address].mtx.lock();
	data_mem[address].data_ = value;
	data_mem[address].mtx.unlock();
	return 0;
}
ReadInst::~ReadInst() {}