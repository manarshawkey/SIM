#pragma once
#include"instruction.h"
#include<iostream>
#include<vector>
#include"Data_Mem.h"
//assign in1, out
class AssignInst : public instruction {
public:
	AssignInst(int, int, bool, std::vector<Data_Mem>::pointer);
	virtual int execute();
	~AssignInst();
private:
	int in, out;
	bool flag;
	std::vector<Data_Mem>::pointer data_mem;
};
AssignInst::AssignInst(int op1, int op2, bool flg, std::vector<Data_Mem>::pointer data)
	: data_mem(&data[0]), flag(flg), in(op1), out((op2 <= 0 || op2 > 1023) ? throw std::invalid_argument("Invalid mem address\n") : op2) {}
int AssignInst::execute() {
	if (flag) {
		data_mem[in].mtx.lock();
		in = data_mem[in].data_;
		data_mem[in].mtx.unlock();
	}
	data_mem[out].mtx.lock();
	data_mem[out].data_ = in;
	data_mem[out].mtx.unlock();
	return 0;
}
AssignInst::~AssignInst() {}
