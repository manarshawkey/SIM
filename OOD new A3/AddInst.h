#pragma once
#include"instruction.h"
#include<iostream>
#include<vector>
#include"Data_Mem.h"
class AddInst : public instruction {
public:
	AddInst(int, int, int, bool, bool, std::vector<Data_Mem>::pointer);
	virtual int execute();
	~AddInst();
private:
	int in1, in2, out;
	bool flag1, flag2;
	std::vector<Data_Mem>::pointer data_mem;
};
AddInst::AddInst(int op1, int op2, int op3, bool flg1, bool flg2, std::vector<Data_Mem>::pointer data)
	: data_mem(&data[0]), flag1(flg1), flag2(flg2), in1(op1), in2(op2),
	  out((op3 <= 0 || op3 > 1023) ? throw std::invalid_argument("Invalid mem location\n") : op3) {}
int AddInst::execute() {
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
	data_mem[out].mtx.lock();
	data_mem[out].data_ = in1 + in2;
	data_mem[out].mtx.unlock();
	return 0;
}
AddInst::~AddInst() {}