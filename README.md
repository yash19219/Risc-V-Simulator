# Risc V ASSEMBLER
C++ Program taking assembly code as input in the form of string and converting it in binary code Instruction of 32-bit and then storing it into a file "binary.txt". <br/>
Here is the referenced used for converting assembly code to binary is : https://msyksphinz-self.github.io/riscv-isadoc/html/rvi.html#ebreak. <br/>
All conversion is based on formats present in RISC – V Reference Sheet available in Project. <br/>

# Risc V Simulator
We have designed a simulator that simulates a subset of RISCV(RV32) ISA in C++. The main components of this simulator are Main Memory, registers, instruction register,<br/> program counter(pc)<br/>
This simulator has 5 stages:<br/>
• Instruction Fetch:  New instructions to be executed are loaded from the memory into the instruction register<br/>
• Decoding: The fetched instruction are decoded i.e. the simulator identifies the type of the instruction and the values of the required registers are also read.<br/>
• Execution: Different operations are performed as defined in the instruction<br/>
• Memory: If there is a need of accessing the memory, then this stage helps in loading and storing the values in the main memory.<br/>
• Writeback: In this stage, the values are written in the registers<br/>

The workflow of our simulator is as follows:<br/>
First, it loads the input binary(compiled by our assembler) in the main memory, and then it starts executing the code at the address 0.<br/>
Each instruction is then passed from the above mentioned 5 stages of our simulator

# Test Cases
we have added many test cases  <br/>
user can take input from there

# Support
OUR PROGRAM IS ABLE TO PERFORM THE FOLLOWING INSTRUCTIONS:-

•	ADD     ->        Addition <br/>
•	ADDI 	 -> 	        Add Immediate <br/>
•	SUB 	 -> 	Subtraction <br/>
•	LW 	 -> 	Load word <br/>
•	SW 		 ->  Store Word <br/>
•	JALR 	 -> 	Jump and Link Register <br/>
•	JAL 	 -> 	Jump and Link  <br/>
•	BEQ 	 -> 	Branch Equal to <br/>
•	BNE 	 -> 	Branch Not equal to <br/>
•	BLT		 ->  Branch Less than <br/>
•	BGE 	 -> 	Branch greater than equal <br/>
•	LUI 	 -> 	Load Upper Immediate <br/>
•	AND 	 -> 	AND <br/>
•	OR 	 -> 	OR <br/>
•	XOR 	 -> 	XOR <br/>
•	SLL 	 -> 	Shift Logical left <br/>
•	SRA 	 -> 	Shift Right Arithmetic <br/>



# Built With/ Concepts Used
•	C++ complier is required to run this program   \
•	RISC – V (32-Bit Architecture)

# How to build program (In Compiler)
->	open ca.cpp and then run the file <br/>
->	input.txt will contain assembly code <br/>
->	binary.txt will contain all the instruction in 32-bit binary form <br/>
->	output.txt will contain the final output  <br/>

## Final Report 
![1](pic/cachetyp.jpg)
![2](pic/1.jpg)
![3](pic/2.jpg)
![4](pic/3.jpg)
![5](pic/4.jpg)

