#include<bits/stdc++.h>
using namespace std;
#include "MainMemory.h"

class Simulator {

public:
	int registers[32];


	int pc = 0;
	MainMemory mem;
	string instruction;

	string R = "0110011";
	string I = "0010011";
	string L = "0000011";
	string S = "0100011";
	string B = "1100011";
	string U = "0110111";
	string JALR = "1100111";
	string JAL = "1101111";

	Simulator(int memSize, int memAccessTime) {
		mem.setSize(memSize);
		mem.setAccessTime(memAccessTime);
		for (int i = 0; i < 32; i++) {
			registers[i] = 0;
		}
	}
	void fetch() {
		instruction = mem.memory[pc];
		pc = pc + 1;
	}

	vector<string> decode() {
		vector<string> v;
		string opt = instruction.substr(25, 7);
		string c;
		if (opt.compare(R) == 0) {
			c = instruction.substr(17, 3);
			if (c.compare("000") == 0) {
				if (instruction.substr(0, 7).compare("0000000") == 0) {
					v.push_back("add");
				}
				else if (instruction.substr(0, 7).compare("0100000") == 0) {
					v.push_back("sub");
				}
				else {
					cout << "INVALID Instruction!!!!\n";
				}
			}
			else if (c.compare("001")) {
				if (instruction.substr(0, 7).compare("0000000") == 0) {
					v.push_back("sll");
				}
				else {
					cout << "INVALID Instruction!!!!\n";
				}
			}
			else if (c.compare("100")) {
				if (instruction.substr(0, 7).compare("0000000") == 0) {
					v.push_back("xor");
				}
				else {
					cout << "INVALID Instruction!!!!\n";
				}
			}
			else if (c.compare("101")) {
				if (instruction.substr(0, 7).compare("0100000") == 0) {
					v.push_back("sra");
				}
				else {
					cout << "INVALID Instruction!!!!\n";
				}
			}
			else if (c.compare("110")) {
				if (instruction.substr(0, 7).compare("0000000") == 0) {
					v.push_back("or");
				}
				else {
					cout << "INVALID Instruction!!!!\n";
				}
			}
			else if (c.compare("111")) {
				if (instruction.substr(0, 7).compare("0000000") == 0) {
					v.push_back("and");
				}
				else {
					cout << "INVALID Instruction!!!!\n";
				}
			}
			else {
				cout << "INVALID INSTRUCTION\n";
			}

			v.push_back(instruction.substr(20, 5)); //rd
			v.push_back(instruction.substr(12, 5)); //rs1
			v.push_back(instruction.substr(7, 5)); //rs2


		}

		else if (opt.compare(I) == 0) {
			c = instruction.substr(17, 3);
			if (c.compare("000") == 0) {
				v.push_back("addi");
			}
			else {
				cout << "INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(20, 5)); //rd
			v.push_back(instruction.substr(12, 5)); //rs1
			v.push_back(instruction.substr(0, 12)); //imm
		}

		else if (opt.compare(L) == 0) {
			c = instruction.substr(17, 3);
			if (c.compare("010") == 0) {
				v.push_back("lw");
			}
			else {
				cout << "INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(20, 5)); //rd
			v.push_back(instruction.substr(12, 5)); //rs1
			v.push_back(instruction.substr(0, 12)); //imm
		}

		else if (opt.compare(S) == 0) {
			c = instruction.substr(17, 3);
			if (c.compare("010") == 0) {
				v.push_back("sw");
			}
			else {
				cout << "INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(12, 5)); //rs1
			v.push_back(instruction.substr(7, 5));  //rs2
			v.push_back(instruction.substr(0, 7) + instruction.substr(20, 5)); //offset
		}

		else if (opt.compare(B) == 0) {
			c = instruction.substr(17, 3);
			if (c.compare("000") == 0) {
				v.push_back("beq");
			}
			else if (c.compare("001") == 0) {
				v.push_back("bne");
			}
			else if (c.compare("100") == 0) {
				v.push_back("blt");
			}
			else if (c.compare("101") == 0) {
				v.push_back("bge");
			}
			else {
				cout << "INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(12, 5)); //rs1
			v.push_back(instruction.substr(7, 5));  //rs2
			v.push_back(instruction.substr(0, 1) + instruction.substr(24, 1) + instruction.substr(1, 6) + instruction.substr(20, 5) + "0"); //offset
		}

		else if (opt.compare(U) == 0) {
			v.push_back("lui");
			cout << "lui ke andar" << endl;
			v.push_back(instruction.substr(20, 5)); //rd
			v.push_back("000000000000" + instruction.substr(0, 20)); //imm
			cout << v[1] << " " << v[2] << endl;

		}

		else if (opt.compare(JAL) == 0) {
			v.push_back("jal");

			v.push_back(instruction.substr(20, 5)); //rd
			v.push_back(instruction.substr(11, 1) + instruction.substr(21, 10) + instruction.substr(20, 1) + instruction.substr(12, 8)); ///check not confirmed :( last mai 12 zeros add karne hai shyd??
		}

		else if (opt.compare(JALR) == 0) {
			c = instruction.substr(17, 3);
			if (c.compare("000") == 0) {
				v.push_back("jalr");
			}
			else {
				cout << "INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(20, 5)); //rd
			v.push_back(instruction.substr(12, 5)); //rs1
			v.push_back(instruction.substr(0, 12)); //offset
		}

		else {
			cout << "INVALID Instruction!!!!\n";
		}
		return v;
	}


	int execute(vector<string> v) {
		cout << "inside exe " << v[0] << endl;
		if (v[0].compare("add") == 0) {
			return add(v[1], v[2], v[3]);
		}
		else if (v[0].compare("sub") == 0) {
			return sub(v[1], v[2], v[3]);
		}
		else if (v[0].compare("sll") == 0) {
			return sll(v[1], v[2], v[3]);
		}
		else if (v[0].compare("xor") == 0) {
			return Xor(v[1], v[2], v[3]);
		}
		else if (v[0].compare("sra") == 0) {
			return sra(v[1], v[2], v[3]);
		}
		else if (v[0].compare("or") == 0) {
			return Or(v[1], v[2], v[3]);
		}
		else if (v[0].compare("and") == 0) {
			return And(v[1], v[2], v[3]);
		}
		else if (v[0].compare("addi") == 0) {
			return addi(v[1], v[2], v[3]);
		}
		else if (v[0].compare("beq") == 0) {
			beq(v[1], v[2], v[3]);
			return -1;
		}
		else if (v[0].compare("bne") == 0) {
			bne(v[1], v[2], v[3]);
			return -1;
		}
		else if (v[0].compare("blt") == 0) {
			blt(v[1], v[2], v[3]);
			return -1;
		}
		else if (v[0].compare("bge") == 0) {
			bge(v[1], v[2], v[3]);
		}
		else if (v[0].compare("lui") == 0) {
			return lui(v[1], v[2]);
		}
		else if (v[0].compare("jalr") == 0) {
			jalr(v[1], v[2], v[3]);
			return -1;
		}
		else if (v[0].compare("jal") == 0) {
			jal(v[1], v[2]);
			return -1;
		}
		else if (v[0].compare("lw") == 0) {
			return lw(v[1], v[2], v[3]);
		}
		else if (v[0].compare("sw") == 0) {
			return sw(v[1], v[2], v[3]);
		}
		else {
			cout << "SOME ERROR" << endl;
		}
		return 0;
	}

	int memory(vector<string> v, int val) {
		if (v[0].compare("lw") == 0) {
			return stoi(mem.memory[val], 0, 2);
		}
		else if (v[0].compare("sw") == 0) {
			mem.memory[val] = stoi(v[2], 0, 2);
			return 0;
		}
		else {
			return val;
		}
		return 0;
	}


	void writeBack(vector<string> s, int value) {
		if (s[0].compare("beq") == 0 or s[0].compare("bne") == 0 or s[0].compare("bge") == 0 or s[0].compare("blt") == 0 or s[0].compare("sw") == 0 )
			return ;
		else
			registers[stoi(s[1], 0, 2)] = value;
	}

	int add(string rd, string rs1, string rs2) {
		int a = stoi(rs1, 0, 2);
		int b = stoi(rs2, 0, 2);
		int result = registers[a] + registers[b];
		return result;
		//registers[stoi(rd),0,2]=result;

	}

	int addi(string rd, string rs1, string imm) {
		int a = stoi(rs1, 0, 2);
		int b = stoi(imm, 0, 2);
		int result = registers[a] + b;
		return result;
		//registers[stoi(rd),0,2]=result;

	}

	int sub(string rd, string rs1, string rs2) {
		int a = stoi(rs1, 0, 2);
		int b = stoi(rs2, 0, 2);
		int result = registers[a] - registers[b];
		return result;
		//registers[stoi(rd),0,2]=result;

	}

	int lw(string rd, string rs1, string offset) {
		int a = stoi(rs1, 0, 2);
		int b = stoi(rd, 0, 2);
		int off = stoi(offset, 0, 2);
		return registers[a] + off;
		//return stoi(mem.memory[registers[a]+off],0,2);
		//registers[b]=mem[registers[a]+off];

	}

	int sw(string rs1, string rs2, string offset) {
		int a = stoi(rs1, 0, 2);
		int b = stoi(rs2, 0, 2);
		int off = stoi(offset, 0, 2);
		return registers[a] + off;
		//mem.memory[registers[a]+off]=bitset<32>(registers[b]).to_string();
	}


	void jalr(string rd, string rs1, string offset) {

	}

	void jal(string rd, string offset) {

	}

	void beq(string rs1, string rs2, string offset) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs1, 0, 2)];

		if (a == b) {
			int c = stoi(offset, 0, 2);
			pc = pc + (c / 4);
		}

	}

	void bne(string rs1, string rs2, string offset) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs1, 0, 2)];

		if (a != b) {
			int c = stoi(offset, 0, 2);
			pc = pc + (c / 4);
		}
	}

	void blt(string rs1, string rs2, string offset) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs1, 0, 2)];

		if (a < b) {
			int c = stoi(offset, 0, 2);
			pc = pc + (c / 4);
		}
	}

	void bge(string rs1, string rs2, string offset) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs1, 0, 2)];

		if (a >= b) {
			int c = stoi(offset, 0, 2);
			pc = pc + (c / 4);
		}
	}

	int lui(string rd, string imm) {
		int a = stoi(rd, 0, 2);

		// for(int i=31;i>=31-12;i--){
		// 	imm[i]='0';
		// }
		return stoi(imm, 0, 2);
		//registers[a]=stoi(imm,0,2);

	}

	int And(string rd, string rs1, string rs2) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs2, 0, 2)];

		return a & b;
		//registers[stoi(rd,0,2)]=a&b;
	}

	int Or(string rd, string rs1, string rs2) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs2, 0, 2)];
		return a | b;

		//registers[stoi(rd,0,2)]=a|b;
	}

	int Xor(string rd, string rs1, string rs2) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs2, 0, 2)];

		return a ^ b;
		//registers[stoi(rd,0,2)]=a^b;
	}

	int sll(string rd, string rs1, string rs2) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs2, 0, 2)];

		return a << b;
		//registers[stoi(rd,0,2)]=a<<b;
	}

	int sra(string rd, string rs1, string rs2) {
		int a = registers[stoi(rs1, 0, 2)];
		int b = registers[stoi(rs2, 0, 2)];

		return a >> b;
		//registers[stoi(rd,0,2)]=a>>b;
	}

	void RFDump() {
		for (int i = 0; i < 8; i++) {
			cout << "R" << i << ": " << registers[i] << "    ";
		}
		cout << endl;
		for (int i = 8; i < 16; i++) {
			cout << "R" << i << ": " << registers[i] << "    ";
		}
		cout << endl;
		for (int i = 16; i < 24; i++) {
			cout << "R" << i << ": " << registers[i] << "    ";
		}
		cout << endl;
		for (int i = 24; i < 32; i++) {
			cout << "R" << i << ": " << registers[i] << "    ";
		}
		cout << endl;

	}


};