#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <string>

namespace ASM
{
	/*
		Everying in this namespace can be accessed by ASM::name
		
		For example:
		ASM::REGISTER_SIZE
		ASM::PeekNextCommandIndex(<arguments>)
		ASM::ADD(<arguments>)
	*/

	// Number of registers this implementation support
	constexpr int REGISTER_SIZE = 8;

	// ################################## //
	// ###### EXPOSED ASSEMBLER API ##### //
	// ################################## //

	// General command construction and reading

	bool BuildCommandList(std::vector<std::vector<std::string>>& commandList, std::string filepath);
	int PeekNextCommandIndex(int* registers);
	int GetAndStepCommandIndex(int* registers);

	// Assignment intructions

	void MOV(std::vector<std::string>& command, int* registers);
	
	// Arithmetic instructions

	void ADD(std::vector<std::string>& command, int* registers);
	void SUB(std::vector<std::string>& command, int* registers);
	
	// Conditional instructions

	void CMP(std::vector<std::string>& command, int* registers);
	void JEQ(std::vector<std::string>& command, int* registers);
	void JGT(std::vector<std::string>& command, int* registers);
	void JLT(std::vector<std::string>& command, int* registers);
}

#endif