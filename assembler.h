#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL)
using namespace std;


#define deb(x) cout << #x << " " << x << endl
#define deb1(x,y) cout<<#x<<" "<<x<<" , "<<#y<<" "<<y<<endl
#define deb2(x,y,z) cout<<#x<<" "<<x<<" , "<<#y<<" "<<y<<" , "<<#z<<" "<<z<<endl
#define ll long long int
#define endn "\n"
#define M 1000000007
const long long INF = 1e18;
const int N = 2e5 + 5;
#define MAX_NAME_LEN 1000
class Assembler {

	vector<string> instructions;
	map<string, int> label;
	map<int, int> procedure;
	map<string, int> procedureName;


public:

	string add(string rs1, string rs2, string rd) {
		string ans = "";
		ans = "0000000" + rs2 + rs1 + "000" + rd + "0110011";
		return ans;
	}

	string sub(string rs1, string rs2, string rd) {
		string ans = "";
		ans = "0100000" + rs2 + rs1 + "000" + rd + "0110011";
		return ans;
	}

	string annd(string rs1, string rs2, string rd) {
		string ans = "";
		ans = "0000000" + rs2 + rs1 + "111" + rd + "0110011";
		return ans;
	}

	string oor(string rs1, string rs2, string rd) {
		string ans = "";
		ans = "0000000" + rs2 + rs1 + "110" + rd + "0110011";
		return ans;
	}

	string xorr(string rs1, string rs2, string rd) {
		string ans = "";
		ans = "0000000" + rs2 + rs1 + "100" + rd + "0110011";
		return ans;
	}

	string sll(string rs1, string rs2, string rd) {
		string ans = "";
		ans = "0000000" + rs2 + rs1 + "001" + rd + "0110011";
		return ans;
	}

	string sra(string rs1, string rs2, string rd) {
		string ans = "";
		ans = "0100000" + rs2 + rs1 + "101" + rd + "0110011";
		return ans;
	}



	string addi(string rs1, int c, string rd) {
		string ans = "";
		string rv = bitset<12> (c).to_string();
		ans = rv + rs1 + "000" + rd + "0010011";
		return ans;
	}

	string lw(string rs1, int c, string rd) {
		string ans = "";
		string rv = bitset<12> (c).to_string();
		ans = rv + rs1 + "010" + rd + "0000011";
		return ans;
	}

	string jalr(string rs1, string rd) {
		string ans = "";
		int c = 0;
		string rv = bitset<12> (c).to_string();
		//	deb2(rv, rs1, rd);
		ans = rv + rs1 + "000" + rd + "1100111";
		return ans;
	}

	string jal(string rd, string r, int f) {
		string ans = "";
		int c = procedureName[r];
		c -= f;
		string rv = bitset<20> (c).to_string();
		ans = rv[rv.size() - 1] + rv.substr(0, 10) + rv[10] + rv.substr(11, 8) + rd + "1101111";
		return ans;
	}


	string sw(string rs1, int c, string rd) {
		string ans = "";
		string rv2 = bitset<12> (c).to_string();
		string rv = rv2.substr(0, 7);
		string rv1 = rv2.substr(7, 5);
		ans = rv + rd + rs1 + "010" + rv1 + "0100011";
		return ans;

	}


	string lui(string rd, int c) {
		string ans = "";
		string rv = bitset<32> (c).to_string();

		ans = rv.substr(12, 20) + rd + "0110111";
		return ans;

	}


	string beq(string rs1, string rs2, int cur, string str) {
		int cind = 0;
		for (auto x : label) {
			if (x.first == str) {
				cind = x.second;
				break;
			}
		}

		int final = cind - cur;



		string ans = "";
		string rv = bitset<12> (final).to_string();
		//deb2(rv, final, rs1);

		ans = rv[0] + rv.substr(2, 6) + rs2 + rs1 + "000" + rv.substr(8, 4) + rv[1] + "1100011";
		return ans;

	}


	string bne(string rs1, string rs2, int cur, string str) {
		int cind = 0;
		for (auto x : label) {
			if (x.first == str) {
				cind = x.second;
				break;
			}
		}

		int final = cind - cur;



		string ans = "";
		string rv = bitset<12> (final).to_string();

		ans = rv[0] + rv.substr(2, 6) + rs2 + rs1 + "001" + rv.substr(8, 4) + rv[1] + "1100011";
		return ans;

	}

	string blt(string rs1, string rs2, int cur, string str) {
		int cind = 0;
		for (auto x : label) {
			if (x.first == str) {
				cind = x.second;
				break;
			}
		}

		int final = cind - cur;



		string ans = "";
		string rv = bitset<12> (final).to_string();

		ans = rv[0] + rv.substr(2, 6) + rs2 + rs1 + "100" + rv.substr(8, 4) + rv[1] + "1100011";
		return ans;

	}

	string bge(string rs1, string rs2, int cur, string str) {
		int cind = 0;
		for (auto x : label) {
			if (x.first == str) {
				cind = x.second;
				break;
			}
		}

		int final = cind - cur;



		string ans = "";
		string rv = bitset<12> (final).to_string();

		ans = rv[0] + rv.substr(2, 6) + rs2 + rs1 + "101" + rv.substr(8, 4) + rv[1] + "1100011";
		return ans;

	}




	vector<string> Rinst() {
		return instructions;
	}

	map<int,int> getProc(){
		return procedure;
	}



	void binaryGenerate(string line[], int n) {
		map<string, string> registers;
		int ar = 0;
		int addr = -1;

		map<int, vector<string>> nlines;
		int ng = 0;
		int prev=-1;
		for (int i = 0; i < n; i++) {
			vector<string> temp;
			string g = "";
			for (int i1 = 0; i1 < line[i].size(); i1++) {
				if (line[i][i1] == '.') {
					if (g.size() != 0)
						temp.push_back(g);

					g = "";
				}
				else
					g.push_back(line[i][i1]);

			}
			if (temp.size() == 1) {
				for (int i2 = 0; i2 < temp[0].size(); i2++)
					if (temp[0][i2] >= 65 && temp[0][i2] <= 92)
					{
						temp[0][i2] = temp[0][i2] + 32;
					}
				procedureName[temp[0].substr(0, temp[0].size() - 1)] = i - ng;
				prev = i - ng;
				ng++;
			}
			else {
				string temp1 = temp[0];

				for (int i2 = 0; i2 < temp[0].size(); i2++)
					if (temp[0][i2] >= 65 && temp[0][i2] <= 92)
					{
						temp[0][i2] = temp[0][i2] + 32;
					}
				if (temp[0] == "jalr") {
					procedure[prev] = i - ng;
					prev = -1;
				}
				nlines[i - ng] = temp;
			}

		}

		for (int i1 = 0; i1 < nlines.size(); i1++) {
			for (int i = 0; i < nlines[i1].size(); i++) {
				for (int i2 = 0; i2 < nlines[i1][i].size(); i2++)
					if (nlines[i1][i][i2] >= 65 && nlines[i1][i][i2] <= 92)
					{
						nlines[i1][i][i2] = nlines[i1][i][i2] + 32;
					}
			}

		}


		// for (int i1 = 0; i1 < nlines.size(); i1++) {
		// 	deb(i1);
		// 	for (int i = 0; i < nlines[i1].size(); i++) {

		// 		cout << nlines[i1][i] << " ";

		// 	}
		// 	cout << endl;

		// }






		for (int i = 0; i < 32; i++) {
			string rv = bitset<5> (i).to_string();
			string ii = to_string(i);
			registers["r" + ii] = rv;


		}

		for (int i1 = 0; i1 < nlines.size(); i1++) {
			string op = nlines[i1][0];
			int last = 0;

			if (op[op.size() - 1] == ':') {
				// ANMOL TEZ MT CHL

				label[op.substr(0, op.size() - 1)] = i1;


			}
		}




		for (int i1 = 0; i1 < nlines.size(); i1++) {
			if (nlines[i1].size() == 1)
				continue;
			int last = 0;
			string op = nlines[i1][last];

			if (op[op.size() - 1] == ':') {
				op = nlines[i1][last + 1];
				last = last + 1;
			}

			if (op == "add") {

				string rs1 = "", rs2 = "", rd = "";
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				rs2 = registers[nlines[i1][last + 3]];


				string ans = add(rs1, rs2, rd);
				instructions.push_back(ans);

			}
			else if (op == "addi") {
				string rs1 = "", rd = "";

				//vector<string> a = type2(last, i1, line);
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				int val = stoi(nlines[i1][last + 3]);


				string ans = addi(rs1, val, rd);
				instructions.push_back(ans);

			}
			else if (op == "sub") {
				string rs1 = "", rs2 = "", rd = "";
				//vector<string> a = type1(last, i1, line);
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				rs2 = registers[nlines[i1][last + 3]];


				string ans = sub(rs1, rs2, rd);
				instructions.push_back(ans);


			}
			else if (op == "lw") {
				// rd int(rs1)
				string rs1 = "", rd = "";

				//vector<string> a = type3(last, i1, line);
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 3]];
				int val = stoi(nlines[i1][last + 2]);


				string ans = lw(rs1, val, rd);
				instructions.push_back(ans);

			}
			else if (op == "sw") {
				// rd int(rs1)
				string rs1 = "", rd = "";

				//vector<string> a = type3(last, i1, line);
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 3]];
				int val = stoi(nlines[i1][last + 2]);


				string ans = sw(rs1, val, rd);
				instructions.push_back(ans);

			}
			else if (op == "jalr") {
				// rd rs1 offset
				string rd = nlines[i1][last + 1];
				string rs1 = nlines[i1][last + 2];



				string ans = jalr(registers[rs1], registers[rd]);
				instructions.push_back(ans);




			}
			else if (op == "jal") {
				// rd offset
				//ar = i1 + 1;
				string rd = "", r = "";

				//vector<string> a = type4(last, i1, line);
				rd = registers[nlines[i1][last + 1]];



				string ans = jal(rd, nlines[i1][last + 2], i1);
				instructions.push_back(ans);
				deb(ans);




			}

			else if (op == "beq") {

				string rs1 = "", rs2 = "";
				//vector<string> a = type2(last, i1, line);
				rs1 = registers[nlines[i1][last + 1]];
				rs2 = registers[nlines[i1][last + 2]];
				//deb(a[2]);

				string ans = beq(rs1, rs2, i1, nlines[i1][last + 3]);
				instructions.push_back(ans);


			}
			else if (op == "bne") {
				string rs1 = "", rs2 = "";
				//vector<string> a = type2(last, i1, line);
				rs1 = registers[nlines[i1][last + 1]];
				rs2 = registers[nlines[i1][last + 2]];
				//deb(a[2]);

				string ans = bne(rs1, rs2, i1, nlines[i1][last + 3]);
				instructions.push_back(ans);

			}
			else if (op == "blt") {
				string rs1 = "", rs2 = "";
				rs1 = registers[nlines[i1][last + 1]];
				rs2 = registers[nlines[i1][last + 2]];
				string ans = blt(rs1, rs2, i1, nlines[i1][last + 3]);
				instructions.push_back(ans);

			}
			else if (op == "bge") {
				string rs1 = "", rs2 = "";
				rs1 = registers[nlines[i1][last + 1]];
				rs2 = registers[nlines[i1][last + 2]];
				string ans = bge(rs1, rs2, i1, nlines[i1][last + 3]);
				instructions.push_back(ans);

			}
			else if (op == "lui") {
				string rs1 = "";

				//	vector<string> a = type3(last, i1, line);

				rs1 = registers[nlines[i1][last + 1]];
				int val = stoi(nlines[i1][last + 2]);


				string ans = lui(rs1, val);
				instructions.push_back(ans);

			}
			else if (op == "and") {
				string rs1 = "", rs2 = "", rd = "";
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				rs2 = registers[nlines[i1][last + 3]];


				string ans = annd(rs1, rs2, rd);
				instructions.push_back(ans);

			}
			else if (op == "or") {
				string rs1 = "", rs2 = "", rd = "";
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				rs2 = registers[nlines[i1][last + 3]];


				string ans = oor(rs1, rs2, rd);
				instructions.push_back(ans);

			}
			else if (op == "xor") {
				string rs1 = "", rs2 = "", rd = "";
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				rs2 = registers[nlines[i1][last + 3]];


				string ans = xorr(rs1, rs2, rd);
				instructions.push_back(ans);

			}
			else if (op == "sll") {
				string rs1 = "", rs2 = "", rd = "";
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				rs2 = registers[nlines[i1][last + 3]];


				string ans = sll(rs1, rs2, rd);
				instructions.push_back(ans);

			}
			else if (op == "sra") {
				string rs1 = "", rs2 = "", rd = "";
				rd = registers[nlines[i1][last + 1]];
				rs1 = registers[nlines[i1][last + 2]];
				rs2 = registers[nlines[i1][last + 3]];


				string ans = sra(rs1, rs2, rd);
				instructions.push_back(ans);

			}

		}




	}

};