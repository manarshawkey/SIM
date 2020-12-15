#pragma once
#include"instruction.h"
#include<iostream>	
#include"Data_Mem.h"
//Write addr: print the value of x in the console
class WriteInst : public instruction {
public:
	WriteInst(int, bool, std::vector<Data_Mem>::pointer);
	virtual int execute();
	~WriteInst();
private:
	int value;
	bool flg;
	std::vector<Data_Mem>::pointer data_mem;
};
WriteInst::WriteInst(int val, bool flg, std::vector<Data_Mem>::pointer data)
	: data_mem(&data[0]), value(val), flg(flg) {}
int WriteInst::execute() {
	if (flg) {
		if (value < 1 || value > 1023)
			throw std::invalid_argument("Invalid mem address\n");
		data_mem[value].mtx.lock();
		std::cout << data_mem[value].data_ << std::endl;
		data_mem[value].mtx.unlock();
	} 
	else
		std::cout << value << std::endl;
	return 0;
}
WriteInst::~WriteInst() {}