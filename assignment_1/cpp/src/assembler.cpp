#include "assembler.hpp"

#include <fstream>
#include <iostream>
#include <sstream>


int GetRegIndex(std::string str) {
  std::stringstream ss;
	int num;
	ss << str[1];
	ss >> num;
	return num;
}

int GetConstant(std::string str) { //rätt
  std::stringstream ss;
	int num;
	ss << str.substr(1, str.length());
	ss >> num;
	return num;
}

bool IsReg(std::string str) {
	return (str[0] == 'R');
}

int ExtractValue(std::string str, int *registers) {
  if (IsReg(str)) {
		return registers[GetRegIndex(str)];
	}
	return GetConstant(str);
}

// public
int ASM::PeekNextCommandIndex(int* registers) {
  return registers[ASM::REGISTER_SIZE-1];
}

bool ASM::BuildCommandList(std::vector<std::vector<std::string>>& commandList, std::string filepath){
  commandList.clear();
	std::ifstream r_file(filepath);

	if (!r_file.is_open()) {
		return false;
	}

	std::string line;
	std::string word = "";
	std::vector<std::string> temp;
	std::vector<std::string> labelNames;
	std::vector<std::string> labelRows;
	bool flag;
	while(getline(r_file, line)) {
		temp.clear();
		temp.shrink_to_fit();
		flag = true;
		if (line.length() == 0) {}
		else {
		for (int i = 0; i < line.size(); i++) {
				if (line[i] == ':') {
					labelNames.push_back(word);
					labelRows.push_back(std::to_string(commandList.size()));
					word.clear();
					flag = false;

				} else {
				if (line[i] == ' ') {
					temp.push_back(word);
					word.clear();
			} else{
				if(line[i] != '\r') {
				word += line[i];}
			} }
		}

		if (flag) {
      temp.push_back(word); //troligen där bad malloc
		// word.pop_back();
		commandList.push_back(temp);
		word.clear();
  }
	}
	line.clear();
	}
	for (size_t i = 0; i < commandList.size(); i++) {
		if (commandList[i][0] == "JEQ" || commandList[i][0] == "JGT" || commandList[i][0] == "JLT") {
			int index = -1;
			for (size_t e = 0; e < labelNames.size(); e++) {
				if (labelNames[e] == commandList[i][1]) {
					index = e;
					commandList[i][1] = labelRows[index];
				}
			}
		}
	}
	return true;
}

int ASM::GetAndStepCommandIndex(int* registers) {
  int index = registers[ASM::REGISTER_SIZE-1];
  registers[ASM::REGISTER_SIZE-1] += 1;
  return index;
}

// assembly functions

void ASM::MOV(std::vector<std::string>& command, int* registers) {
  int destIndex = GetRegIndex(command[1]);
  int value = ExtractValue(command[2], registers);
  registers[destIndex] = value;
}

void ASM::ADD(std::vector<std::string>& command, int* registers){
  int destIndex = GetRegIndex(command[1]);
  int term1 = ExtractValue(command[2], registers);
  int term2 = ExtractValue(command[3], registers);
  registers[destIndex] = term1 + term2;


}
void ASM::SUB(std::vector<std::string>& command, int* registers){
  int destIndex = GetRegIndex(command[1]);
  int term1 = ExtractValue(command[2], registers);
  int term2 = ExtractValue(command[3], registers);
  registers[destIndex] = term1 - term2;
}

// Conditional instructions

void ASM::CMP(std::vector<std::string>& command, int* registers) {
  int value1 = ExtractValue(command[1], registers);
  int value2 = ExtractValue(command[2], registers);

  if (value1 == value2) {
		registers[ASM::REGISTER_SIZE-2] = 1;
  }
  if (value1 > value2) {
    registers[ASM::REGISTER_SIZE-2] = 2;
  }
  if (value1 < value2) {
		registers[ASM::REGISTER_SIZE-2] = 3;
  }
}

void ASM::JEQ(std::vector<std::string>& command, int* registers) {
if (registers[ASM::REGISTER_SIZE-2] == 1) {
  registers[ASM::REGISTER_SIZE-1] = std::stoi(command[1]);
}}

void ASM::JGT(std::vector<std::string>& command, int* registers) {
  if (registers[ASM::REGISTER_SIZE-2] == 2) {
    registers[ASM::REGISTER_SIZE-1] = std::stoi(command[1]);
}}

void ASM::JLT(std::vector<std::string>& command, int* registers) {
  if (registers[ASM::REGISTER_SIZE-2] == 3) {
    registers[ASM::REGISTER_SIZE-1] = std::stoi(command[1]);
}}
