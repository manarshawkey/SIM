#pragma once
#pragma once
#include<iostream>
#include<string>
#include"instruction.h"
//int mem[1023];
class ArithmeticInst :public instruction {
public:
	ArithmeticInst(std::string, int, int, int);
	virtual int execute();
private:
	int oprnd1, oprnd2;
	std::string type;
};
ArithmeticInst::ArithmeticInst(std::string type, int oprnd1, int oprnd2, int des)
	:instruction(des),
	type(type), oprnd1(oprnd1), oprnd2(oprnd2) {
}
int ArithmeticInst::execute() {
	int address = instruction::des;
	if (type == "ADD") {
		mem[address] = oprnd1 + oprnd2;
	}
	else if (type == "MUL") {
		mem[address] = oprnd1 * oprnd2;
	}
	else if (type == "LE") {
		if (oprnd1 <= oprnd2)
			mem[address] = 1;
		else
			mem[address] = 0;
	}
	std::cout << mem[address] << std::endl;
	return -1;
}
