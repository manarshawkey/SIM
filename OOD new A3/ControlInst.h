#pragma once
#include<iostream>
#include<string>
#include"instruction.h"
class ControlInst :public instruction {
public:
	ControlInst(std::string, int, int);
	int execute();
private:
	std::string type;
	int oprnd1;
};
ControlInst::ControlInst(std::string type, int op2, int op1)
	:instruction((type == "JMP") ? op2 : op1), type(type), oprnd1(op1) {
}
//execute returns an address to be fed to the program counter
int ControlInst::execute() {
	if (type == "JMP") {
		return instruction::des;
	}
	if (oprnd1 == 0)
		return instruction::des;
	return -1;  //jump0 & n!= 0
}
