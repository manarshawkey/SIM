#pragma once
#include"instruction.h"
#include<iostream>
#include<vector>
#include"Data_Mem.h"
//LE in1, in2, out
//out must be an address
class LessEqInst : public instruction {
public:
	LessEqInst(int, int, int, bool, bool, std::vector<Data_Mem>::pointer);
	virtual int execute();
	~LessEqInst();
private:
	int in1, in2, out;
	bool flag1, flag2;
	std::vector<Data_Mem>::pointer data_mem;
};
LessEqInst::LessEqInst(int op1, int op2, int op3, bool flg1, bool flg2, std::vector<Data_Mem>::pointer data)
	: data_mem(&data[0]), flag1(flg1), flag2(flg2), in1(op1), in2(op2),
	out((op3 <= 0 || op3 > 1023) ? throw std::invalid_argument("Invalid mem location\n") : op3) {}
int LessEqInst::execute() {
	if (flag1) {
		data_mem[in1].mtx.lock();
		in1 = data_mem[in1].data_;
		data_mem[in1].mtx.unlock();
	}
	if (flag2) {
		data_mem[in2].mtx.lock();
		in2 = data_mem[in2].data_;
		data_mem[in2].mtx.unlock();
	}
	if (in1 <= in2) {
		data_mem[out].mtx.lock();
		data_mem[out].data_ = 1;
		data_mem[out].mtx.unlock();
	}
	else {
		data_mem[out].mtx.lock();
		data_mem[out].data_ = 0;
		data_mem[out].mtx.unlock();
	}
	return 0;
}
LessEqInst::~LessEqInst() {}
