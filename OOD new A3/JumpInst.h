#pragma once
#include"instruction.h"
#include<iostream>
#include"Data_Mem.h"
class JumpInst :public instruction {
	//jump a1, a1 is an address
public:
	JumpInst(int, std::vector<Data_Mem>::pointer);
	virtual int execute();
	~JumpInst();
private:
	int address;
	std::vector<Data_Mem>::pointer data_mem;
};
JumpInst::JumpInst(int addr, std::vector<Data_Mem>::pointer data)
	:data_mem(&data[0]), 
	address((addr> 1023 || addr < 1)? throw std::invalid_argument("invalid address"):addr) {}
int JumpInst::execute() {
	return address;
}
JumpInst::~JumpInst() {}
