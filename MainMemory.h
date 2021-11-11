#include<bits/stdc++.h>
using namespace std;


class MainMemory{
	
	
	public:
		string *memory;
		int size;
		float accessTime;
		
		void setSize(int size1){
			size=size1;
			memory=new string[size];
			for(int i=0;i<size;i++){
				memory[i]=bitset<32>(0).to_string();
			}
		}
		void setAccessTime(float access){
			accessTime=access;
		}

		void dump(){
			cout<<"\n\n";
			cout<<"Memory Location\t\t\t\t\t\tValue Stored"<<endl;
			for(int i=0;i<size;i++){
				cout<<bitset<32>(i).to_string()<<"\t\t\t"<<memory[i]<<endl;
			}
		}
};