#include<bits/stdc++.h>
using namespace std;


class MainMemory{
	
	
	public:
		string *memory;
		int size;
		int accessTime;
		// MainMemory(int s=256,int access=0.01){
		// 	size=s;
		// 	memory=new int[s];
		// 	accessTime=access;
		// }

		void setSize(int size){
			memory=new string[size];
			for(int i=0;i<size;i++){
				memory[i]="0";
			}
		}
		void setAccessTime(int access){
			accessTime=access;
		}
};