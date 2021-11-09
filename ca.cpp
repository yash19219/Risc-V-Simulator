#include<bits/stdc++.h>
#include "Simulator.h"
#include "assembler.h"
using namespace std;

int main(){

	// Assembler assembler;
	// int n = 0;

	// FILE *pp=freopen("input.txt", "r", stdin);
	// FILE *fp=freopen("binary.txt","w",stdout);

	// //freopen("binary.txt", "w", stdout);



	// vector<string> lines;
	// string str;
	// while (getline(cin, str)) {
	// 	n++;
	// 	lines.push_back(str);
	// 	//cout << str << endn;
	// }
	// string line[n];
	// for (int i = 0; i < n; i++) {
	// 	line[i] = lines[i];
	// }


	// assembler.binaryGenerate(line, n);
	// map<int, string> instruction = assembler.Rinst();

	// for (auto x : instruction) {
	// 	cout <<  x.second << endn;
	// 	//cout << 1 << endn;
	// }

	// fclose(pp);
	// fclose(fp);


	vector<string> instructions;

	freopen("binary.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string str1;
	while(getline(cin,str1)){
		instructions.push_back(str1);
	}
	cout<<instructions.size()<<endl;
	cout<<"The input is: "<<endl;
	for(string i:instructions){
		cout<<i<<endl;
	}
	Simulator sim(256,1);
	for(int i=0;i<instructions.size();i++){
		sim.mem.memory[i]=instructions[i];
	}

	for(int i=0;i<instructions.size();i++){
		
		cout<<i<<endl;

		//Fetching 
		sim.fetch();

		cout<<"IR: "<<sim.instruction<<endl;

		vector<string> s;

		cout<<"Before decode"<<endl;
		//Decoding
		s=sim.decode();

		cout<<"After decode"<<endl;
		cout<<s[0]<<" "<<s[1]<<" "<<s[2]<<endl;

		cout<<"Before exe"<<endl;
		//EXECUTION 
		int a=sim.execute(s);

		cout<<"Before mem"<<endl;
		//Memory
		int b=sim.memory(s,a);

		cout<<"Before writeBack"<<endl;
		//Writeback
		sim.writeBack(s,b);	

		sim.RFDump();

		cout<<"\n\n-----------------------------------------------\n";

	}


}