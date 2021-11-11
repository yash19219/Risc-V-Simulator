# Risc 5 Simulator
We have designed a simulator that simulates a subset of RISCV(RV32) ISA in C++. The maine components of this simulator are Main Memory, registers, instruction register, program counter(pc)
This simulator has 5 stages:
1)Instruction Fetch:  New instructions to be executed are loaded from the memory into the instruction register
2)Decoding: The fetched instruction are decoded i.e. the simulator identifies the type of the instruction and the values of the required registers are also read.
3)Execution: Different operations are performed as defined in the instruction
4)Memory: If there is a need of accessing the memory, then this stage helps in loading and storing the values in the main memory.
5)Writeback: In this stage, the values are written in the registers

The workflow of our simulator is as follows:
First, it loads the input binary(compiled by our assembler) in the main memory, and then it starts executing the code at the address 0.
Each instruction is then passed from the above mentioned 5 stages of our simulator


# Test Cases
Test Cases for several Programs such as Sorting, Factorial is provided in the project for better understanding.

# Support
The Project currently supports all instructions available in format.txt file. Pseudo instructions such as Load Address and Load Word (due to data part) is also handled.

# Built With/ Concepts Used
•	C ++      \
•	RISC – V (32-Bit Architecture)

# How to build program (In Compiler)
•	Type following  \
->	Place the code to translate in test.asm File  \
->	Compile A-to-M.cpp  \
->	Output will be produced in MCode.mc File  \
->	MCode.mc has Machine Code in Hexadecimal Form with Program Counter followed by Data Memory Part.


# Built By
	Kritagya Agarwal
