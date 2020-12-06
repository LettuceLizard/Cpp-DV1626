import sys
import assembler as ASM

def main():
	# Sanity check file to read in args
	if (len(sys.argv) <= 1 or len(sys.argv) > (ASM.REGISTER_SIZE+1)):
		print("Error: Invalid argument list.")
		print("\nFormat: python3 interpreter.py program.asm (R0) (R1) (R3) (R4) ... (R7)")
		print("\nArgument list explanationd:")
		print("(REQUIRED) program.asm : The executable assembly file")
		print("(OPTIONAL) (R0) : Default value for the register R0")
		print("(OPTIONAL) (R1) : Default value for the register R1")
		print("(OPTIONAL) (R2) : Default value for the register R2")
		print("(OPTIONAL) (R3) : Default value for the register R3")
		print("(OPTIONAL) (...) : Default value for the register ...")
		print("(OPTIONAL) (R7) : Default value for the register R7")
		return

	# Initialize registers, default all to 0
	# The all until last index is free to use by
	# the executable .asm files for storing values.
	# The last index is used as the 'next command index',
	# which is the next command to execute in the command list
	registers = [0] * ASM.REGISTER_SIZE

	# Read default values of registers in arguments (if any)
	for i in range(2, len(sys.argv)):
		registers[i-2] = int(sys.argv[i])

	# Initialize an empty command list
	#
	# The command list is a list of lists,
	# with each sub-list containing a "formatted command"
	# for easy reading and usage by indexing.
	#
	# Example of appearance:
	# [ ["MOV", "R0", "#3"], ["MOV", "R1", "#-15"], ["ADD", "R0", "R0", "R1"] ]
	commands = []

	# Try to build the command list
	if not ASM.BuildCommandList(commands, sys.argv[1]):
		print(f"Error: Could not open file {sys.argv[1]}.")
		return

	# Execute all commands until 'next command index' is
	# out of range (of indices in the command list)
	while ASM.PeekNextCommand(registers) < len(commands):
		command = commands[ASM.GetAndStepCommandIndex(registers)]
		
		if (command[0] == "MOV"):
			ASM.MOV(command, registers)

		elif (command[0] == "ADD"):
			ASM.ADD(command, registers)
		elif (command[0] == "SUB"):
			ASM.SUB(command, registers)
		
		elif (command[0] == "CMP"):
			ASM.CMP(command, registers)
		elif (command[0] == "JEQ"):
			ASM.JEQ(command, registers)
		elif (command[0] == "JGT"):
			ASM.JGT(command, registers)
		elif (command[0] == "JLT"):
			ASM.JLT(command, registers)

	# End the application by printing the four first registers,
	# separated by a space
	reg_line = ""
	for i in range(4):
		reg_line += str(registers[i]) + " "
	print(reg_line)

if __name__ == "__main__":
	main()