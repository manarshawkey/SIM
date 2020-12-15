#pragma once
#include<iostream>
#include<mutex>
class Data_Mem
{
public:
	Data_Mem() {}
	~Data_Mem() {}
	std::mutex mtx;
	int data_;
private:
};
