#pragma once
#include<iostream>
class instruction {
public:
	instruction();
	virtual int execute() = 0;
	~instruction();
};
instruction::instruction() {
}
instruction::~instruction() {}
