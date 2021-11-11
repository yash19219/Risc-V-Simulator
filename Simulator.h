#include<bits/stdc++.h>
using namespace std;
#include "MainMemory.h"


// This is the class of our Simulator

class Simulator{

public:
	int registers[32];
	int pc=0;
	MainMemory mem;
	string instruction;

	string R="0110011";
	string I="0010011";
	string L="0000011";
	string S="0100011";
	string B="1100011";
	string U="0110111";
	string JALR="1100111";
	string JAL="1101111";


	//contructor of the class to initialize or simulator
	Simulator(int memSize,float memAccessTime){
		mem.setSize(memSize);
		mem.setAccessTime(memAccessTime);
		for(int i=0;i<32;i++){
		registers[i]=0;
		}
	}

	//function to fetch the instruction
	void fetch(map<int,int> m){
		cout<<"PC: "<<pc<<endl;
		instruction=mem.memory[pc];
		pc=pc+1;	
		if(m.find(pc)==m.end() or registers[31]!=0){
			
			pc=pc;	
		}
		else{
			pc=m[pc]+1;
		}
		
	}


	//function to decode the instruction
	vector<string> decode(){
		vector<string> v;
		string opt=instruction.substr(25,7);
		string c;
		if(opt.compare(R)==0){
			c=instruction.substr(17,3);
			if(c.compare("000")==0){
				if(instruction.substr(0,7).compare("0000000")==0){
					v.push_back("add");
				}
				else if(instruction.substr(0,7).compare("0100000")==0){
					v.push_back("sub");
				}
				else{
					cout<<"INVALID Instruction!!!!\n";
				}
			}
			else if(c.compare("001")==0){
				if(instruction.substr(0,7).compare("0000000")==0){
					v.push_back("sll");
				}
				else{
					cout<<"INVALID Instruction!!!!\n";
				}
			}
			else if(c.compare("100")==0){
				if(instruction.substr(0,7).compare("0000000")==0){
					v.push_back("xor");
				}
				else{
					cout<<"INVALID Instruction!!!!\n";
				}	
			}
			else if(c.compare("101")==0){
				if(instruction.substr(0,7).compare("0100000")==0){
					v.push_back("sra");
				}
				else{
					cout<<"INVALID Instruction!!!!\n";
				}
			}
			else if(c.compare("110")==0){
				if(instruction.substr(0,7).compare("0000000")==0){
					v.push_back("or");
				}
				else{
					cout<<"INVALID Instruction!!!!\n";
				}
			}
			else if(c.compare("111")==0){
				if(instruction.substr(0,7).compare("0000000")==0){
					v.push_back("and");
				}
				else{
					cout<<"INVALID Instruction!!!!\n";
				}
			}
			else{
				cout<<"INVALID INSTRUCTION\n";
			}

			v.push_back(instruction.substr(20,5)); //rd
			v.push_back(instruction.substr(12,5)); //rs1
			v.push_back(instruction.substr(7,5));  //rs2
			

		}

		else if(opt.compare(I)==0){
			c=instruction.substr(17,3);
			if(c.compare("000")==0){
				v.push_back("addi");
			}
			else{
				cout<<"INVALID Instruction!!!!\n";
			}
	
			v.push_back(instruction.substr(20,5));  //rd
			v.push_back(instruction.substr(12,5));  //rs1
			v.push_back(instruction.substr(0,12)); //imm
		}

		else if(opt.compare(L)==0){
			c=instruction.substr(17,3);
			if(c.compare("010")==0){
				v.push_back("lw");
			}
			else{
				cout<<"INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(20,5));  //rd
			v.push_back(instruction.substr(12,5));  //rs1
			v.push_back(instruction.substr(0,12)); //imm
		}

		else if(opt.compare(S)==0){
			c=instruction.substr(17,3);
			if(c.compare("010")==0){
				v.push_back("sw");
			}
			else{
				cout<<"INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(12,5));  //rs1
			v.push_back(instruction.substr(7,5));   //rs2
			v.push_back(instruction.substr(0,7)+instruction.substr(20,5));  //offset
		}

		else if(opt.compare(B)==0){
			c=instruction.substr(17,3);
			if(c.compare("000")==0){
				v.push_back("beq");
			}
			else if(c.compare("001")==0){
				v.push_back("bne");
			}
			else if(c.compare("100")==0){
				v.push_back("blt");
			}
			else if(c.compare("101")==0){
				v.push_back("bge");
			}
			else{
				cout<<"INVALID Instruction!!!!\n";
			}

			v.push_back(instruction.substr(12,5));  //rs1
			v.push_back(instruction.substr(7,5));   //rs2
			v.push_back(instruction.substr(0,1)+instruction.substr(24,1)+instruction.substr(1,6)+instruction.substr(20,4));  //offset
		}

		else if(opt.compare(U)==0){
			v.push_back("lui");
			cout<<"lui ke andar"<<endl;
			v.push_back(instruction.substr(20,5));  //rd
			v.push_back(instruction.substr(0,20)+"000000000000");   //imm
			cout<<v[1]<<" "<<v[2]<<endl;

		}

		else if(opt.compare(JAL)==0){
			v.push_back("jal");

			v.push_back(instruction.substr(20,5));  //rd
			string offset=instruction.substr(1,19)+instruction.substr(0,1);
			v.push_back(offset);
			//v.push_back(instruction.substr(11,1)+instruction.substr(21,10)+instruction.substr(20,1)+instruction.substr(12,8)); ///check not confirmed :( last mai 12 zeros add karne hai shyd??
		}

		else if(opt.compare(JALR)==0){
			c=instruction.substr(17,3);
			if(c.compare("000")==0){
				v.push_back("jalr");
				v.push_back(instruction.substr(20,5));  //rd
				v.push_back(instruction.substr(12,5));  //rs1
				v.push_back(instruction.substr(0,12));  //offset
			}
			else{
				cout<<"INVALID Instruction!!!!\n";
			}

			
		}

		else{
			cout<<"INVALID Instruction!!!!\n";
		}
		return v;
	}

	//funtion to execute the current instruction
	int execute(vector<string> v){
		cout<<"inside exe "<<v[0]<<endl;
		if(v[0].compare("add")==0){
			return add(v[1],v[2],v[3]);
		}
		else if(v[0].compare("sub")==0){
			return sub(v[1],v[2],v[3]);
		}
		else if(v[0].compare("sll")==0){
			return sll(v[1],v[2],v[3]);
		}
		else if(v[0].compare("xor")==0){
			return Xor(v[1],v[2],v[3]);
		}
		else if(v[0].compare("sra")==0){
			return sra(v[1],v[2],v[3]);
		}
		else if(v[0].compare("or")==0){
			return Or(v[1],v[2],v[3]);
		}
		else if(v[0].compare("and")==0){
			return And(v[1],v[2],v[3]);
		}
		else if(v[0].compare("addi")==0){
			return addi(v[1],v[2],v[3]);
		}
		else if(v[0].compare("beq")==0){
			 beq(v[1],v[2],v[3]);
			 return -1;
		}
		else if(v[0].compare("bne")==0){
			bne(v[1],v[2],v[3]);
			return -1;
		}
		else if(v[0].compare("blt")==0){
			blt(v[1],v[2],v[3]);
			return -1;
		}
		else if(v[0].compare("bge")==0){
			bge(v[1],v[2],v[3]);
		}
		else if(v[0].compare("lui")==0){
			return lui(v[1],v[2]);
		}
		else if(v[0].compare("jalr")==0){
			int a= jalr(v[1],v[2],v[3]);
			cout<<"IF JALR-------------- "<<registers[31]<<" return value"<<a<<endl;
			return a;
		}
		else if(v[0].compare("jal")==0){
			return jal(v[1],v[2]);
		}
		else if(v[0].compare("lw")==0){
			return lw(v[1],v[2],v[3]);
		}
		else if(v[0].compare("sw")==0){
			return sw(v[1],v[2],v[3]);
		}
		else{
			cout<<"SOME ERROR"<<endl;
		}
	}


	//function which helps in accessing the memory(performs load and store operations)
	int memory(vector<string> v,int val){
		if(v[0].compare("lw")==0){
			return stoi(mem.memory[val],0,2);
		}
		else if(v[0].compare("sw")==0){
			mem.memory[val] = bitset<32>(registers[stoi(v[2],0,2)]).to_string();
			cout<<"IN MEMORY : "<<val<<" "<<stoi(mem.memory[val],0,2)<<endl;
			return 0;
		}
		else{
			return val;
		}
	}


	//function to write the values in register
	void writeBack(vector<string> s,int value){
		if(s[0].compare("beq")==0 or s[0].compare("bne")==0 or s[0].compare("bge")==0 or s[0].compare("blt")==0 or s[0].compare("sw")==0 )
			return ;
		else
			registers[stoi(s[1],0,2)]=value;
	}



	//helper functions that perform different kinds of operations

	int add(string rd, string rs1, string rs2){
		int a=stoi(rs1,0,2);
		int b=stoi(rs2,0,2);
		int result=registers[a]+registers[b];
		return result;
		//registers[stoi(rd),0,2]=result;
		
	}

	int addi(string rd,string rs1, string imm){
		int a=stoi(rs1,0,2);
		int b=stoi(imm,0,2);
		if(b>2047){
			b-=4096;
		}
		int result=registers[a]+b;
		return result;
		//registers[stoi(rd),0,2]=result;

	}

	int sub(string rd, string rs1, string rs2){
		int a=stoi(rs1,0,2);
		int b=stoi(rs2,0,2);
		int result=registers[a]-registers[b];
		return result;
		//registers[stoi(rd),0,2]=result;
		
	}

	int lw(string rd,string rs1,string offset){
		int a=stoi(rs1,0,2);
		int b=stoi(rd,0,2);
		int off=stoi(offset,0,2);
		if(off>2047){
			off-=4096;
		}
		return registers[a]+off;
		//return stoi(mem.memory[registers[a]+off],0,2);
		//registers[b]=mem[registers[a]+off];

	}

	int sw(string rs1,string rs2,string offset){
		int a=stoi(rs1,0,2);
		int b=stoi(rs2,0,2);
		int off=stoi(offset,0,2);
		if(off>2047){
			off-=4096;
		}
		cout<<"offset "<<offset<<endl;
		return registers[a]+off;
		//mem.memory[registers[a]+off]=bitset<32>(registers[b]).to_string();
	}


	int jalr(string rd,string rs1,string offset){
		int a=pc;
		pc=registers[stoi(rs1,0,2)]+stoi(offset,0,2);
		cout<<"INSIDE JALR "<<pc<<endl;
		registers[31]=0;
		cout<<"31 "<<registers[31]<<endl;
		return a;

	}

	int jal(string rd,string offset){
		int a=pc;
		cout<<"IN JAL "<<offset<<endl;
		int c=stoi(offset,0,2);
			if(c>524287){
				c-=1048576;
			}
			cout<<"int offset "<<c<<endl;
		pc+=c-1;
		return a;


	}

	void beq(string rs1,string rs2,string offset){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];
		if(a==b){
			int c=stoi(offset,0,2);
			if(c>2047){
				c-=4096;
			}
			pc=pc+c-1;

		}

	}

	void bne(string rs1,string rs2,string offset){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];
		if(a!=b){
			int c=stoi(offset,0,2);
			if(c>2047){
				c-=4096;
			}
			pc=pc+c-1;

		}
	}

	void blt(string rs1,string rs2,string offset){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];
		if(a<b){
			int c=stoi(offset,0,2);
			if(c>2047){
				c-=4096;
			}
			pc=pc+c-1;

		}
	}

	void bge(string rs1,string rs2,string offset){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];
		if(a>=b){
			int c=stoi(offset,0,2);
			if(c>2047){
				c-=4096;
			}
			pc=pc+c-1;

		}
	}

	int lui(string rd,string imm){
		int a=stoi(rd,0,2);

		cout<<"in lui "<<imm<<endl;
		cout<<"hello"<<endl;
		cout<<imm.length()<<endl;
		long long int b=stoll(imm,0,2);
		if(b>(pow(2,31)-1)){
			b-=pow(2,32);
		}

		cout<<"inlui : "<<b<<endl;
		return (int)b;
		//registers[a]=stoi(imm,0,2);

	}

	int And(string rd, string rs1,string rs2){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];

		return (a&b);
		//registers[stoi(rd,0,2)]=a&b;
	}

	int Or(string rd, string rs1,string rs2){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];
		return a|b;

		//registers[stoi(rd,0,2)]=a|b;
	}

	int Xor(string rd, string rs1,string rs2){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];

		return a^b;
		//registers[stoi(rd,0,2)]=a^b;
	}

	int sll(string rd, string rs1,string rs2){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];
		string s=bitset<32>(b).to_string().substr(27,5);
		int c=stoi(s,0,2);
		return a<<c;
		//registers[stoi(rd,0,2)]=a<<b;
	}

	int sra(string rd, string rs1,string rs2){
		int a=registers[stoi(rs1,0,2)];
		int b=registers[stoi(rs2,0,2)];
		string s=bitset<32>(b).to_string().substr(27,5);
		int c=stoi(s,0,2);
		if(a>=0)
			return a>>c;
		string d=bitset<32>(a).to_string().substr(0,32-c);
		string e="";
		for(int i=0;i<c;i++){
			e+="1";
		}
		e+=d;
		long long int x=stoll(e,0,2);
		if(x>(pow(2,31)-1)){
			x-=pow(2,32);
		}
		return (int)x;

		//registers[stoi(rd,0,2)]=a>>b;
	}


	//function that print the values of the registers
	void RFDump(){
		for(int i=0;i<8;i++){
			cout<<"R"<<i<<": "<<registers[i]<<"    ";
		}
		cout<<endl;
		for(int i=8;i<16;i++){
			cout<<"R"<<i<<": "<<registers[i]<<"    ";
		}
		cout<<endl;
		for(int i=16;i<24;i++){
			cout<<"R"<<i<<": "<<registers[i]<<"    ";
		}
		cout<<endl;
		for(int i=24;i<32;i++){
			cout<<"R"<<i<<": "<<registers[i]<<"    ";
		}
		cout<<endl;

	}


};