#include<bits/stdc++.h>
using namespace std;
//#include "MainMemory.h"
#define deb(x) cout << #x << " " << x << endl
#define deb1(x,y) cout<<#x<<" "<<x<<" , "<<#y<<" "<<y<<endl
#define deb2(x,y,z) cout<<#x<<" "<<x<<" , "<<#y<<" "<<y<<" , "<<#z<<" "<<z<<endl


class Cache {
public:

	string *tag;
	string *data;
	string *dirtyBit;

	string wPolicy, rPolicy;
	float hitTime;
	int size, missPenalty, associativity, blockSize;

	int cnt;
	int *counter;

	vector<priority_queue<pair<int, string>>> lru;

	Cache(int s, int MissPenalty, int HitTime, int BlockSize, int Assocativity, string write, string replace) {
		size = s;
		missPenalty = MissPenalty;
		hitTime = HitTime;
		blockSize = BlockSize;
		associativity = Assocativity;
		wPolicy = write;
		rPolicy = replace;


		srand (time(NULL));

		tag = new string[s];
		dirtyBit = new string[s];
		data = new string[s];
		counter = new int[size / associativity];

		cout << "THE NUMBER OF SETS ARE: " << size / associativity << endl;

		for (int i = 0; i < s; i++) {
			tag[i] = "";
			data[i] = "";
			dirtyBit[i] = "0";

		}
		for (int i = 0; i < size / associativity; i++) {
			priority_queue<pair<int, string>> lru1;
			lru.push_back(lru1);
		}

		// tag[8]=bitset<30>(20).to_string();
		// tag[9]=bitset<30>(4).to_string();



		cnt = 0;

		for (int i = 0; i < size / associativity; i++) {
			counter[i] = 0;
		}

	}


	pair<bool, pair<string, int>> hit_miss(string address) {
		string Tag = address.substr(0, 30);
		cout << "IN CACHE HIT_MISS\n" << endl;
		if (associativity == 1) {
			//direct mapped
			int indx = log2(size);
			string Index = Tag.substr(30 - indx, indx);
			cout << " index dm" << " " << Index << endl;
			int indexInt = stoi(Index, 0, 2);

			if (tag[indexInt] == Tag) {
				return {true, {data[indexInt], indexInt}};
			}
			return {false, {"-1", -1}};
		}

		else if (associativity == size) {
			// fully associative
			for (int i = 0; i < size; i++) {
				if (tag[i] == Tag) {
					if (rPolicy == "LRU") {
						int a = isFull(address);
						if (a == -1) {
							string x = lruSetter(0, Tag);
						}
						else {
							lruPush(0, Tag);
						}

					}

					return {true, {data[i], i}};
				}

			}
			if (rPolicy == "LRU") {
				int a = isFull(address);
				if (a != -1) {
					lruPush(0, Tag);
				}
			}

			return {false, {"-1", -1}};

		}

		else {
			// k way associative
			int indx = log2(size / associativity);
			string Index = Tag.substr(30 - indx, indx);
			cout << " index k-way2" << " " << Index << endl;
			int indexInt = stoi(Index, 0, 2);
			for (int i = indexInt * associativity; i < (indexInt + 1 )* associativity; i++) {
				if (tag[i] == Tag) {
					if (rPolicy == "LRU") {
						int a = isFull(address);
						if (a == -1) {
							string x = lruSetter(indexInt, Tag);
						}
						else {
							lruPush(indexInt, Tag);
						}
					}
					return {true, {data[i], i}};
				}
			}
			if (rPolicy == "LRU") {
				int a = isFull(address);
				//deb(a);
				if (a != -1) {
					deb("yash");
					lruPush(indexInt, Tag);
				}
			}
			return {false, {"-1", -1}};
		}

	}


	int isFull(string address) {
		string Tag = address.substr(0, 30);
		cout << "IN CACHE ISFULL\n" << endl;
		if (associativity == 1) {
			int indx = log2(size);
			string Index = Tag.substr(30 - indx, indx);
			int indexInt = stoi(Index, 0, 2);

			if (tag[indexInt] == "") {
				return indexInt;
			}
			return -1;
		}

		else if (associativity == size) {

			for (int i = 0; i < size; i++) {
				if (tag[i] == "")
					return i;

			}
			return -1;
		}

		else {
			int indx = log2(size / associativity);
			string Index = Tag.substr(30 - indx, indx);
			cout << " index k-way1" << " " << Index << endl;
			//deb(lru.size());
			int indexInt = stoi(Index, 0, 2);

			for (int i = indexInt * associativity; i < (indexInt + 1 )* associativity; i++) {
				if (tag[i] == "") {
					deb(i);
					return i;
				}
			}

			return -1;
		}

	}

	int replace(string address, MainMemory mem) {
		cout << "IN CACHE REPLACE!!!!!\n" << endl;
		string Tag = address.substr(0, 30);
		//deb(lru.size());
		cout << "rrrrrrrrrrrrr " << rPolicy << endl;
		if (rPolicy == "FIFO") {
			int a = FIFO(address, mem);
			return a;
		}

		else if (rPolicy == "Random") {
			return Random(address, mem);
		}

		else if (rPolicy == "LRU") {
			cout << "!!!!!!!!!!!!!!!!!!!\n";
			return LRU(address, mem);

		}
		else {
			cout << "WRONG replace\n";
			return -1;
		}

	}

	int FIFO(string address, MainMemory mem) {
		cout << "IN CACHE FIFO\n" << endl;
		string Tag = address.substr(0, 30);

		if (associativity == 1) {
			int indx = log2(size);
			string index = Tag.substr(30 - indx, indx);
			int indexInt = stoi(index, 0, 2);

			if (wPolicy == "writeBack" and dirtyBit[indexInt] == "1") {
				mem.memory[stoi(tag[indexInt], 0, 2)] = data[indexInt];
				dirtyBit[indexInt] = "0";
			}

			else if (wPolicy == "writeBack")
				dirtyBit[indexInt] = "1";

			// tag[indexInt] = Tag;
			// data[indexInt] = mem.memory[stoi(Tag,0,2)];

			return indexInt;
		}

		else if (associativity == size) {
			int fcnt = cnt % size;

			if (wPolicy == "writeBack" and dirtyBit[fcnt] == "1") {
				mem.memory[stoi(tag[fcnt], 0, 2)] = data[fcnt];
				dirtyBit[fcnt] = "0";
			}
			else if (wPolicy == "writeBack")
				dirtyBit[fcnt] = "1";


			// tag[fcnt] = Tag;
			// data[fcnt] = mem.memory[stoi(Tag,0,2)];
			cnt++;
			return fcnt;
		}

		else {
			cout << "IN K WAY associative\n";
			int indx = log2(size / associativity);
			string index = Tag.substr(30 - indx, indx);
			int indexInt = stoi(index, 0, 2);
			cout << "THE SET IS: " << indexInt << endl;
			int fcnt = counter[indexInt] % associativity;
			cout << "REPLACE NUmber : " << fcnt << endl;
			int r = indexInt * associativity + fcnt;
			cout << "DIRTY KAHI KI: " << dirtyBit[r] << " " << r << endl;
			if (wPolicy == "writeBack") {
				if (dirtyBit[r] == "1") {
					cout << "___________________" << endl;
					mem.memory[stoi(tag[r], 0, 2)] = data[r];
					dirtyBit[r] = "0";
				}
				else {
					dirtyBit[r] = "1";
				}
			}

			// tag[r] = Tag;
			// data[r] = mem.memory[stoi(Tag,0,2)];
			counter[indexInt]++;

			// cout<<"DEBUG : "<<tag[r]<<" "<<data[r]<<endl;
			return r;
		}
	}

	int Random(string address, MainMemory mem) {
		cout << "IN RANDOM\n";
		string Tag = address.substr(0, 30);
		if (associativity == 1) {
			int indx = log2(size);
			string index = Tag.substr(30 - indx, indx);
			int indexInt = stoi(index, 0, 2);

			if (wPolicy == "writeBack" and dirtyBit[indexInt] == "1") {
				mem.memory[stoi(tag[indexInt], 0, 2)] = data[indexInt];
				dirtyBit[indexInt] = "0";
			}
			else if (wPolicy == "writeBack")
				dirtyBit[indexInt] = "1";

			// tag[indexInt] = Tag;
			// data[indexInt] = mem.memory[stoi(Tag,0,2)];

			return indexInt;
		}

		else if (associativity == size) {

			int indexInt = rand() % size;

			if (wPolicy == "writeBack" and dirtyBit[indexInt] == "1") {
				mem.memory[stoi(tag[indexInt], 0, 2)] = data[indexInt];
				dirtyBit[indexInt] = "0";
			}
			else if (wPolicy == "writeBack")
				dirtyBit[indexInt] = "1";

			// tag[indexInt] = Tag;
			// data[indexInt] = mem.memory[stoi(Tag,0,2)];

			return indexInt;
		}

		else {

			int fcnt = rand() % associativity;
			int indx = log2(size / associativity);
			string index = Tag.substr(30 - indx, indx);
			int indexInt = stoi(index, 0, 2) * associativity + fcnt;
			cout << "REPLACE INDEX: " << indexInt << endl;
			if (wPolicy == "writeBack" and dirtyBit[indexInt] == "1") {
				mem.memory[stoi(tag[indexInt], 0, 2)] = data[indexInt];
				dirtyBit[indexInt] = "0";
			}
			else if (wPolicy == "writeBack")
				dirtyBit[indexInt] = "1";

			// tag[indexInt] = Tag;
			// data[indexInt] = mem.memory[stoi(Tag,0,2)];

			return indexInt;


		}

	}

	string lruSetter(int idx, string tag1) {
		deb1(idx, tag1);
		vector<pair<int, string>> store;
		bool found = false;
		deb(lru[idx].size());
		while (!lru[idx].empty()) {
			pair<int, string> a = lru[idx].top();
			lru[idx].pop();
			deb1(a.first, a.second);
			if (a.second != tag1)
				store.push_back({a.first + 1, a.second });
			else
				found = true;

		}

		for (auto x : store) {
			lru[idx].push(x);
		}
		string y = lru[idx].top().second;
		//deb(y);
		if (!found) {
			lru[idx].pop();

		}
		lru[idx].push({1, tag1});

		if (found) {
			return "-1";
		}
		else {

			while (!lru[idx].empty()) {
				pair<int, string> a1 = lru[idx].top();
				lru[idx].pop();
				deb1(a1.first, a1.second);


			}

			return y;
		}



	}


	// kth , value of tag
	void lruPush(int idx, string tag1) {
		vector<pair<int, string>> store;
		deb("hello");


		while (!lru[idx].empty()) {
			deb("a1");
			pair<int, string> a = lru[idx].top();
			lru[idx].pop();
			if (tag1 != a.second)
				store.push_back({a.first + 1, a.second});


		}
		for (auto x : store) {
			lru[idx].push(x);
		}

		lru[idx].push({1, tag1});
		deb(lru[idx].size());


	}

	int LRU(string address, MainMemory mem) {
		cout << "IN LRU\n";
		string Tag = address.substr(0, 30);
		if (associativity == 1) {
			int indx = log2(size);
			string index = Tag.substr(30 - indx, indx);
			int indexInt = stoi(index, 0, 2);

			if (wPolicy == "writeBack" and dirtyBit[indexInt] == "1") {
				mem.memory[stoi(tag[indexInt], 0, 2)] = data[indexInt];
				dirtyBit[indexInt] = "0";
			}
			else if (wPolicy == "writeBack")
				dirtyBit[indexInt] = "1";

			// tag[indexInt] = Tag;
			// data[indexInt] = mem.memory[stoi(Tag,0,2)];

			return indexInt;
		}

		else if (associativity == size) {
			string tagu = lruSetter(0, Tag);
			int fcnt = -1;
			for (int i = 0; i < size; i++) {
				if (tag[i] == tagu) {
					fcnt = i;
					break;
				}

			}

			if (fcnt == -1) {
				cout << "WRONG BRO";
			}

			if (wPolicy == "writeBack" and dirtyBit[fcnt] == "1") {
				mem.memory[stoi(tag[fcnt], 0, 2)] = data[fcnt];
				dirtyBit[fcnt] = "0";
			}
			else if (wPolicy == "writeBack")
				dirtyBit[fcnt] = "1";


			// tag[fcnt] = Tag;
			// data[fcnt] = mem.memory[stoi(Tag,0,2)];
			return fcnt;
		}
		else {
			cout << "IN K WAY associative\n";
			int indx = log2(size / associativity);
			string index = Tag.substr(30 - indx, indx);
			int indexInt = stoi(index, 0, 2);
			// cout<<"THE SET IS: "<<indexInt<<endl;
			// int fcnt = counter[indexInt] % associativity;
			// cout<<"REPLACE NUmber : "<<fcnt<<endl;

			string r1 = lruSetter(indexInt, Tag);
			deb(r1);
			int r = -1;
			//int indexInt = stoi(Index, 0, 2);
			for (int i = indexInt * associativity; i < (indexInt + 1 )* associativity; i++) {
				deb1(i, tag[i]);
				if (tag[i] == r1) {
					r = i;
					break;

				}
			}
			if (r == -1) {
				cout << "WRONG BRO";
			}





			//int r = stoi(index1, 0, 2);
			deb(r);
			cout << "DIRTY KAHI KI2: " << dirtyBit[r] << " " << r << endl;
			if (wPolicy == "writeBack") {
				if (dirtyBit[r] == "1") {
					cout << "___________________" << endl;
					mem.memory[stoi(tag[r], 0, 2)] = data[r];
					dirtyBit[r] = "0";
				}
				else {
					dirtyBit[r] = "1";
				}
			}

			// tag[r] = Tag;
			// data[r] = mem.memory[stoi(Tag,0,2)];

			// cout<<"DEBUG : "<<tag[r]<<" "<<data[r]<<endl;
			return r;
		}
	}

	string read(string address, MainMemory mem) {
		cout << "IN CACHE READ\n";
		cout << "Address Val : " << address << endl;
		string Tag = address.substr(0, 30);

		pair<bool, pair<string, int>> p = hit_miss(address);

		if (p.first) {
			cout << "HIT!!!!!!!!i\n";
			return p.second.first;
		}
		else {
			cout << "Miss!!!!!!!!\n";
			int a = isFull(address);
			if (a == -1) {
				cout << "FULLLLLL!!!!!!!!\n";
				int idx = replace(address, mem);
				cout << "REPLACE: " << idx << endl;
				for (int i = 0; i < size; i++) {
					cout << bitset<32>(i).to_string() << "\t\t\t" << tag[i] << "\t\t\t" << data[i] << endl;
				}
				return data[idx];
			}
			else {
				cout << "NOT FULL\n";
				string val = mem.memory[stoi(Tag, 0, 2)];
				data[a] = val;
				tag[a] = Tag;
				for (int i = 0; i < size; i++) {
					cout << bitset<32>(i).to_string() << "\t\t\t" << tag[i] << "\t\t\t" << data[i] << endl;
				}
				return data[a];
			}
		}


	}

	void write(string address, string value, MainMemory mem) {
		cout << "IN CACHE WRITE\n";
		string Tag = address.substr(0, 30);
		if (wPolicy == "writeThrough") {
			cout << "IN WRITE THROUGH\n";
			pair<bool, pair<string, int>> p = hit_miss(address);
			if (p.first) {
				cout << "HIT!!!!!!!!\n";
				data[p.second.second] = value;
				mem.memory[stoi(Tag, 0, 2)] = value;
			}
			else {
				cout << "Miss!!!!!!!!\n";
				int a = isFull(address);
				if (a == -1) {
					cout << "FULLLLLL!!!!!!!!\n";
					int b = replace(address, mem);
					tag[b] = Tag;
					data[b] = value;
					mem.memory[stoi(tag[b], 0, 2)] = value;
				}
				else {
					cout << "NOT FULL\n";
					tag[a] = Tag;
					data[a] = value;
					mem.memory[stoi(Tag, 0, 2)] = value;
				}

				//data[a]=value;
				//mem.memory[a]=value;   //we are accessing mem two times can do better
			}
		}
		else if (wPolicy == "writeBack") {
			cout << "IN WRITE BACK\n";
			pair<bool, pair<string, int>> p = hit_miss(address);
			if (p.first) {
				cout << "HIT!!!!!!!!\n" << p.second.second << endl;
				data[p.second.second] = value;
				dirtyBit[p.second.second] = "1";
			}
			else {
				cout << "Miss!!!!!!!!\n";
				int a = isFull(address);
				if (a == -1) {
					cout << "FULLLLLL!!!!!!!!\n";
					int b = replace(address, mem);

					tag[b] = Tag;
					data[b] = value;
				}
				else {
					cout << "NOT FULL\n";
					tag[a] = Tag;
					data[a] = value;
					dirtyBit[a] = "1";
				}
				//we are accessing mem two times can do better
			}
		}
	}
	void dump() {
		cout << "\n\n";
		cout << "Memory Location\t\t\t\t\t\t\t\tValue Stored" << endl;
		for (int i = 0; i < size; i++) {
			if (i % associativity == 0) {
				cout << "\n\n\n";
			}
			cout << i << " --> " << tag[i] << "\t\t\t" << data[i] << endl;
		}
	}







} ;
