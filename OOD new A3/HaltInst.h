#pragma once
#include"instruction.h"
#include<iostream>
class HaltInst :public instruction {
public:
	HaltInst();
	virtual int execute();
	~HaltInst();
};
HaltInst::HaltInst() {}
int HaltInst::execute() {
	std::cout << "\nprogram execution is done!\n";
	return -1;
}
HaltInst::~HaltInst() {}
