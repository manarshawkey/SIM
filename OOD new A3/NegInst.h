#pragma once
#include"instruction.h"
#include<iostream>
#include<vector>
#include"Data_Mem.h"
class NegInst : public instruction {
public:
	NegInst(int, int, bool, std::vector<Data_Mem>::pointer);
	virtual int execute();
	~NegInst();
private:
	int in, out;
	bool flag;
	std::vector<Data_Mem>::pointer data_mem;
};
NegInst::NegInst(int op1, int op2, bool flg, std::vector<Data_Mem>::pointer data)
	: data_mem(&data[0]), flag(flg), in(op1), 
	out((op2 <= 0 || op2 > 1023) ? throw std::invalid_argument("Invalid mem address\n") : op2) {}
int NegInst::execute() {
	if (flag) {
		data_mem[in].mtx.lock();
		in = data_mem[in].data_;
		data_mem[in].mtx.unlock();
	}
	data_mem[out].mtx.lock();
	data_mem[out].data_ = -1 * in;
	data_mem[out].mtx.unlock();
	return 0;
}
NegInst::~NegInst() {}

