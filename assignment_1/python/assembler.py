import sys

# Number of registers this implementation support
REGISTER_SIZE = 8

##################################
#### 'PRIVATE' HELP FUNCTIONS ####
##################################

def GetRegIndex(reg : str):
	# Examples of reg strings
	# "R0" : return 0
	# "R1" : return 1
	# Return the second character as an integer
	# Registers only has a single digit
	return int(reg[1])

def GetConstant(const : str):
	# Examples of reg strings
	# "#5" : return 5
	# "#17" : return 17
	# "#-1" : return -1
	# Remove the '#' character,
	# convert rest of string to an integer
	return int(const[1:])

def IsReg(term : str):
	return term[0] == 'R'

def ExtractValue(source : str, registers : list):
	# Check if register or constant
	# If register, return value in that register
	# If constant, return the constant value
	if IsReg(source):
		return registers[GetRegIndex(source)]
	return GetConstant(source)



##################################
###### EXPOSED ASSEMBLER API #####
##################################

# General command construction and reading

def BuildCommandList(commandList : list, filepath : str):

	# Clear previous values (if any)
	commandList.clear()

	# Check if possible to open file
	try:
		file = open(filepath, 'r')
	except FileNotFoundError:
		return False

	# Initialize lists to store the command index
	# if each label, as these are not directly a
	# command and therefore not part of the
	# command list.
	# These are later used after the command list
	# is fully retrieved, to replace each instance
	# of a label with that label's command index.
	labelNames = []
	labelRows = []

	# Read each line from file.
	# For each line:
	# 1. Remove new-line character (if any)
	# 2. Convert into command format
	# 3. Check if label
	#	3a. If label, add information to labelNames and labelRows
	#	3b. If not label, append to command list
	for line in file:
		line = line.replace('\n','')

		if len(line) == 0:
			continue

		lineParts = line.split()

		if lineParts[0][-1] == ':': # Check if label
			lineParts[0] = lineParts[0][:-1] # Remove ':' from label string
			labelNames.append(lineParts[0])
			labelRows.append(str(len(commandList)))
		else:
			commandList.append(lineParts)
	file.close()

	# Once all commands are retrieved, find all conditional
	# jump commands and replace the label names with that
	# label's index as a string instead.
	for command in commandList:
		if command[0] == "JEQ" or command[0] == "JGT" or command[0] == "JLT":
			index = -1
			for i in range(len(labelNames)):
				if labelNames[i] == command[1]:
					index = i
			command[1] = labelRows[index]

	# If this is reached,
	# the build is completed
	return True

def PeekNextCommand(registers : list):
	return registers[REGISTER_SIZE-1]

def GetAndStepCommandIndex(registers : list):
	index = registers[REGISTER_SIZE-1]
	registers[REGISTER_SIZE-1] += 1
	return index

# Assignment intructions

def MOV(command : list, registers : list):
	destIndex = GetRegIndex(command[1])
	value = ExtractValue(command[2], registers)
	registers[destIndex] = value

# Arithmetic instructions

def ADD(command : list, registers : list):
	destIndex = GetRegIndex(command[1])
	term1 = ExtractValue(command[2], registers)
	term2 = ExtractValue(command[3], registers)
	registers[destIndex] = term1 + term2

def SUB(command : list, registers : list):
	destIndex = GetRegIndex(command[1])
	term1 = ExtractValue(command[2], registers)
	term2 = ExtractValue(command[3], registers)
	registers[destIndex] = term1 - term2

# Jump instructions

def CMP(command : list, registers : list):
	value1 = ExtractValue(command[1], registers)
	value2 = ExtractValue(command[2], registers)
	# Compare the two values, and write a specific
	# value to the next to last register determined
	# by the outcome of the comparison.
	# The values are:
	# 1 if both are equal
	# 2 if the first is greater than the second
	# 3 if the first is smaller than the second
	# This value is then read by a jump instruction
	# to determine if the jump will procede or not.
	if value1 == value2:
		registers[REGISTER_SIZE-2] = 1 # 'Equal to'
	elif value1 > value2:
		registers[REGISTER_SIZE-2] = 2 # 'Greater than'
	else: # value1 < value2
		registers[REGISTER_SIZE-2] = 3 # 'Less than'

def JEQ(command : list, registers : list):
	if registers[REGISTER_SIZE-2] == 1: # if equal
		registers[REGISTER_SIZE-1] = int(command[1])

def JGT(command : list, registers : list):
	if registers[REGISTER_SIZE-2] == 2: # if greater than
		registers[REGISTER_SIZE-1] = int(command[1])

def JLT(command : list, registers : list):
	if registers[REGISTER_SIZE-2] == 3: # if less than
		registers[REGISTER_SIZE-1] = int(command[1])