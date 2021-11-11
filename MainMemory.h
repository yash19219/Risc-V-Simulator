#include<bits/stdc++.h>
using namespace std;

//class for Main Memory
class MainMemory{
	
	public:
		string *memory;    //array to store the values
		int size;		   //size of the memory
		float accessTime; //access time of the memory
		
		//function to set the size of the memory
		void setSize(int size1){
			size=size1;
			memory=new string[size];
			for(int i=0;i<size;i++){
				memory[i]=bitset<32>(0).to_string();
			}
		}

		//function to set the access time of the memory
		void setAccessTime(float access){
			accessTime=access;
		}

		//funtion to dump the memory content
		void dump(){
			cout<<"\n\n";
			cout<<"Memory Location\t\t\t\t\t\t\t\tValue Stored"<<endl;
			for(int i=0;i<size;i++){
				cout<<bitset<32>(i).to_string()<<"\t\t\t"<<memory[i]<<endl;
			}
		}
};