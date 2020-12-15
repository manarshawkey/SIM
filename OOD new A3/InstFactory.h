#pragma once
#include"instruction.h"
#include"AddInst.h"
#include"MultInst.h"
#include"AssignInst.h"
#include"LessEqInstruction.h"
#include"NegInst.h"
#include"WriteInst.h"
#include"ReadInst.h"
#include"JumpInst.h"
#include"Jump0Inst.h"
#include"HaltInst.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include"Data_Mem.h"
class InstFactory {
public:
	InstFactory();
	~InstFactory();
	void parse(std::string, std::vector<instruction*>&, std::vector<Data_Mem>::pointer);
private:
	void create_inst_object(std::stringstream&, std::vector<instruction*>& inst_mem, std::vector<Data_Mem>::pointer);
};
InstFactory::InstFactory() {}
void InstFactory::parse(std::string path, std::vector<instruction*>& inst_mem, std::vector<Data_Mem>::pointer data_mem) {
	std::ifstream input;
	input.open(path);
	std::string line;
	std::string operation;
	int oprnd1, oprnd2, oprnd3;
	while (getline(input, line, '\n')) {
		std::stringstream inst_line(line);
		create_inst_object(inst_line, inst_mem, data_mem);
	}
}
InstFactory::~InstFactory() {}
void InstFactory::create_inst_object(std::stringstream& inst_line, std::vector<instruction*>& inst_mem, std::vector<Data_Mem>::pointer data_mem) {
	std::string word, word1;
	inst_line >> word;
	int in, out, in2;
	//neg in, out  //in can be address   @in
	//ass in1, out1
	if (word == "ASS" || word == "NEG") {  
		bool flg = 0;
		inst_line >> word1;
		if (word1[0] == '@') { //an address
			word1.erase(0, 1);
			flg = 1;
			in = std::stoi(word1);
			if (in <= 0 || in > 1023)
				throw(std::invalid_argument("invalid mem loc\n"));
			//in = mem[in];
		}
		else in = std::stoi(word1);  //not an address
		inst_line >> word1;
		if (word1[0] != '@')
			throw std::invalid_argument("an address should start with '@'\n");
		word1.erase(0, 1);
		out = std::stoi(word1);
		if (word == "ASS")
			inst_mem.push_back(new AssignInst(in, out, flg, data_mem));
		else
			inst_mem.push_back(new NegInst(in, out, flg, data_mem));
	}
	else
		if (word == "MUL" || word == "ADD" || word == "LE") {  //changed
			//in1, in2, out
			bool flg1 = 0;
			inst_line >> word1;
			if (word1[0] == '@') {
				flg1 = 1;
				word1.erase(0, 1);
				in = std::stoi(word1);
				if (in <= 0 || in > 1023)
					throw(std::invalid_argument("invalid mem loc\n"));
			}
			else in = std::stoi(word1); //in1

			inst_line >> word1; //in2
			bool flg2 = 0;
			if (word1[0] == '@') {
				flg2 = 1;
				word1.erase(0, 1);
				in2 = std::stoi(word1);
				if (in2 <= 0 || in2 > 1023)
					throw(std::invalid_argument("invalid mem address\n"));
				//in2 = mem[in2];
			}
			else in2 = std::stoi(word1);
			inst_line >> word1;
			if (word1[0] != '@')
				throw std::invalid_argument("an address should start with '@'\n");
			word1.erase(0, 1);
			out = std::stoi(word1);   //validated within instruction constructor

			if (word == "ADD") inst_mem.push_back(new AddInst(in, in2, out, flg1, flg2, data_mem));
			else if (word == "MUL") inst_mem.push_back(new MultInst(in, in2, out, flg1, flg2, data_mem));
			else inst_mem.push_back(new LessEqInst(in, in2, out, flg1, flg2, data_mem));
		}
		else if (word == "READ") {
			inst_line >> word1;
			if (word1[0] != '@') throw std::invalid_argument("an address should start with '@'\n");
			word1.erase(0, 1);
			out = std::stoi(word1);
			inst_mem.push_back(new ReadInst(out, data_mem));
		}
		else if (word == "WRITE") {
			bool flg = 0;
			inst_line >> word1;
			if (word1[0] == '@') {
				flg = 1;
				word1.erase(0, 1);
				out = std::stoi(word1);
				if (out <= 0 || out > 1023) throw (std::invalid_argument("invalid mem location\n"));
				//out = mem[out];
			}
			else out = std::stoi(word1);
			inst_mem.push_back(new WriteInst(out, flg, data_mem));
		}
		else if (word == "HALT") {
			inst_mem.push_back(new HaltInst());
		}
		else if (word == "JUMP") {
			inst_line >> word1;
			if (word1[0] != '@')
				throw std::invalid_argument("an address should start with '@' \n");
			word1.erase(0, 1);
			int addr = stoi(word1);
			if (addr <= 0 || addr > 1023) throw std::invalid_argument("invalid mem location\n");
			inst_mem.push_back(new JumpInst(addr, data_mem));
		}
		else if (word == "JUMP0") {
			inst_line >> word1;
			if (word1[0] == '@') {
				word1.erase(0, 1);
				if (stoi(word1) <= 0 || stoi(word1) > 1023)
					throw std::invalid_argument("invalid mem location\n");
			}
			in = stoi(word1);
			//out must be an address
			inst_line >> word1;
			if (word1[0] != '@')
				throw std::invalid_argument("an address should start with '@'\n");
			word1.erase(0, 1);
			out = stoi(word1);
			inst_mem.push_back(new Jump0Inst(in, out, data_mem));
		}
		else {
			throw std::exception("unexpected token while parsing!\n");
		}
}
