// #include<bits/stdc++.h>
// #include "Simulator.h"
// #include "assembler.h"
// using namespace std;

// int main(){

// 	vector<string> instructions;

// 	freopen("binary.txt","r",stdin);
// 	freopen("output.txt","w",stdout);
// 	string str1;
// 	while(getline(cin,str1)){
// 		instructions.push_back(str1);
// 	}
// 	cout<<instructions.size()<<endl;
// 	cout<<"The input is: "<<endl;
// 	for(string i:instructions){
// 		cout<<i<<endl;
// 	}
// 	Simulator sim(256,1);
// 	for(int i=0;i<instructions.size();i++){
// 		sim.mem.memory[i]=instructions[i];
// 	}

// 	for(int i=0;i<instructions.size();i++){
		
// 		cout<<i<<endl;

// 		//Fetching 
// 		sim.fetch();

// 		cout<<"IR: "<<sim.instruction<<endl;

// 		vector<string> s;

// 		cout<<"Before decode"<<endl;
// 		//Decoding
// 		s=sim.decode();

// 		cout<<"After decode"<<endl;
// 		cout<<s[0]<<" "<<s[1]<<" "<<s[2]<<endl;

// 		cout<<"Before exe"<<endl;
// 		//EXECUTION 
// 		int a=sim.execute(s);

// 		cout<<"Before mem"<<endl;
// 		//Memory
// 		int b=sim.memory(s,a);

// 		cout<<"Before writeBack"<<endl;
// 		//Writeback
// 		sim.writeBack(s,b);	

// 		sim.RFDump();

// 		cout<<"\n\n-----------------------------------------------\n";

// 	}


// }

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
		//cout << str1 << endl;
		instructions.push_back(str1);
	}
	myFile_Handler1.close();
	freopen("output.txt", "w", stdout);
	cout << instructions.size() << endl;
	cout << "The input is: " << endl;
	for (string i : instructions) {
		cout << i << endl;
	}
	Simulator sim(256, 2.5);
	for (int i = 0; i < instructions.size(); i++) {
		sim.mem.memory[i] = instructions[i];
	}


	map<int,int> m=assembler.getProc();
	cout<<"size of m"<<m.size()<<endl;
	for(auto it:m){
		cout<<"proc map"<<it.first<<" "<<it.second<<endl;
	}
	int total_cycles=0;
	float total_time=0.0;
	
	while(sim.pc<instruction.size()){
		//cout << sim.pc << endl;
		int cnt=0;
		//Fetching
		sim.fetch(assembler.getProc());

		cout << "IR: " << sim.instruction << endl;

		vector<string> s;
		
		cout << "Before decode" << endl;
		//Decoding
		s = sim.decode();
		if(s[0]=="lw" or s[0]=="sw"){
			cnt=1;
		}
		cout << "After decode" << endl;
		cout << s[0] << " " << s[1] << " " << s[2] << endl;

		cout << "Before exe" << endl;
		//EXECUTION
		int a = sim.execute(s);

		cout << "Before mem" << endl;
		//Memory
		int b = sim.memory(s, a);

		cout << "Before writeBack" << endl;
		//Writeback
		sim.writeBack(s, b);

		sim.RFDump();


		cout<<"pc  "<<sim.pc+1<<endl;
		float time=5.0;
		if(cnt==1){
			time+=sim.mem.accessTime;
		}
		cout<<"CYCLES SPENT TO PROCESS INSTRUCTION: "<<5<<endl;
		cout<<"TIME TAKEN TO PROCESS INSTRUCTION: "<<time<<endl;
		cout << "\n\n-----------------------------------------------\n";

		total_cycles+=5;

	}
	cout<<"TOTAL CYCLES: "<<total_cycles<<endl;
	sim.mem.dump();

}