

#include<bits/stdc++.h>
#include "Simulator.h"
#include <fstream>

#include "assembler.h"

using namespace std;

int main() {

	Assembler assembler;
	int n = 0;
	fstream myFile_Handler, myFile_Handler1, myFile_Handler2;
	myFile_Handler.open("input.txt", ios::in | ios::out);


	vector<string> lines;
	string str;
	while (getline(myFile_Handler, str)) {
		n++;
		for (int i = 0; i < str.size(); i++)
			if (str[i] == ' ' || str[i] == ',' || str[i] == '(' || str[i] == ')')
				str[i] = '.';
		str.push_back('.');
		lines.push_back(str);
	}
	myFile_Handler.close();

	myFile_Handler1.open("binary.txt", ios::in | ios::out);
	string line[n];
	for (int i = 0; i < n; i++) {
		line[i] = lines[i];
	}


	assembler.binaryGenerate(line, n);
	vector<string> instruction = assembler.Rinst();

	for (auto x : instruction) {
		myFile_Handler1 <<  x << endl;
	}


	vector<string> instructions;

	string str1;
	myFile_Handler1.seekg(ios::beg);
	while (getline(myFile_Handler1, str1)) {
		instructions.push_back(str1);
	}
	myFile_Handler1.close();
	freopen("output.txt", "w", stdout);
	cout << instructions.size() << endl;

	Simulator sim(256, 2.5);
	for (int i = 0; i < instructions.size(); i++) {
		sim.mem.memory[i] = instructions[i];
	}

	cout << "STOI\n";
	for (int i = 0; i < instructions.size(); i++) {
		string a = bitset<32>(i).to_string();
		string b = a.substr(2, 30);

		if (sim.c.associativity == 1) {
			cout << "DONOT ENTER\n";
			int indx = log2(sim.c.size);
			string Index = b.substr(30 - indx, indx);
			int indexInt = stoi(Index, 0, 2);
			sim.c.tag[indexInt] = b;
			sim.c.data[indexInt] = instructions[i];
		}
		else if (sim.c.associativity == sim.c.size) {
			if (i < sim.c.size) {
				//cout << "in\n";
				sim.c.tag[i] = b;
				sim.c.data[i] = instructions[i];
			}
		}
		else {
			cout << "_____\n";
			int indx = log2(sim.c.size / sim.c.associativity);
			string index = b.substr(30 - indx, indx);
			int indexInt = stoi(index, 0, 2);
			int j = 0;
			while (j < sim.c.associativity and sim.c.tag[indexInt * sim.c.associativity + j] != "") {
				j++;
			}
			if (j < sim.c.associativity) {
				sim.c.tag[indexInt * sim.c.associativity + j] = b;
				sim.c.data[indexInt * sim.c.associativity + j] = instructions[i];
			}
		}

	}
	// sim.c.tag[0] = "";
	// sim.c.data[0] = "";

	cout << "OUTTTTTTTTT\n";
	for (int i = 0; i < sim.c.size; i++) {
		if (i % sim.c.associativity == 0) {
			cout << "\n\n\n";
		}
		cout << i << " --> " << sim.c.tag[i] << "\t\t\t" << sim.c.data[i] << endl;
	}
	cout << "\n\n\n-------------------------------------------------------------------\n\n\n";

	map<int, int> m = assembler.getProc();

	int total_cycles = 0;
	float total_time = 0.0;

	while (sim.pc < instruction.size()) {
		int cnt = 0;
		int time = 3;
		//Fetching
		int v = sim.fetch(assembler.getProc());

		time += sim.c.hitTime;

		if (v == -1) {
			time += sim.c.missPenalty;
		}

		cout << "IR: " << sim.instruction << endl;

		vector<string> s;

		cout << "Before decode" << endl;
		//Decoding
		s = sim.decode();
		if (s[0] == "lw" or s[0] == "sw") {
			cnt = 1;
		}
		cout << "After decode" << endl;
		cout << s[0] << " " << s[1] << " " << s[2] << endl;

		cout << "Before exe" << endl;
		//EXECUTION
		int a = sim.execute(s);

		cout << "Before mem" << endl;
		//Memory
		pair<int, int> b = sim.memory(s, a);


		if (s[0] == "lw" or s[0] == "sw")
			time += sim.c.hitTime;

		if (b.second == -1) {
			time += sim.c.missPenalty;
		}

		cout << "Before writeBack" << endl;
		//Writeback
		sim.writeBack(s, b.first);

		sim.RFDump();


		//cout<<"pc  "<<sim.pc+1<<endl;


		cout << "CYCLES SPENT TO PROCESS INSTRUCTION: " << time << endl;
		//cout << "TIME TAKEN TO PROCESS INSTRUCTION: " << time << endl;
		cout << "\n\n-----------------------------------------------\n";

		total_cycles += time;

	}
	cout << "TOTAL CYCLES: " << total_cycles << endl;

	cout << "Total Cache Hits: " << sim.c.hits << endl;
	cout << "Total Cache Misses: " << sim.c.misses << endl;
	cout << "\n\n";
	sim.mem.dump();
	sim.c.dump();

}
