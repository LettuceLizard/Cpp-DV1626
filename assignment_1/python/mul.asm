MOV R2 R0
MOV R0 #0

start:
ADD R0 R0 R2
SUB R1 R1 #1
CMP R1 #0
JGT start

MOV R2 #0