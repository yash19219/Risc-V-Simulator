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

	map<int, string> instructions;
	map<string, int> label;
	map<string, pair<int, int>> procedure;

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
		ans = rv + rs1 + "010" + rd + "0010011";
		return ans;
	}

	string jalr(string rs1, string rd) {
		string ans = "";
		int c = 0;
		string rv = bitset<12> (c).to_string();
		//	deb2(rv, rs1, rd);
		ans = rv + rs1 + "000" + rd + "0010011";
		return ans;
	}

	string jal(string rd, string r) {
		string ans = "";
		int c = procedure[r].first / 4;
		string rv = bitset<20> (c).to_string();
		ans = rv[rv.size() - 1] + rv.substr(0, 10) + rv[10] + rv.substr(11, 8) + rd + "1101111";
		return ans;
	}


	string sw(string rs1, int c, string rd) {
		string ans = "";
		string rv2 = bitset<12> (c).to_string();
		string rv = rv2.substr(0, 7);
		string rv1 = rv2.substr(8, 5);
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

		deb(rv);
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

	vector<string> type1(int last, int i1, string line[]) {
		string rs1 = "", rs2 = "", rd = "";
		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ',') {
				last = i + 2;
				break;
			}
			else
				rd.push_back(line[i1][i]);
		}

		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ',') {
				last = i + 2;
				break;
			}
			else
				rs1.push_back(line[i1][i]);
		}

		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ' ') {
				last = i + 2;
				break;
			}
			else
				rs2.push_back(line[i1][i]);
		}

		vector<string> a;
		a.push_back(rd);
		a.push_back(rs1);
		a.push_back(rs2);

		return a;
	}

	vector<string> type2(int last, int i1, string line[]) {
		string rs1 = "", rs2 = "", r = "";
		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ',') {
				last = i + 2;
				break;
			}
			else
				rs1.push_back(line[i1][i]);
		}

		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ',') {
				last = i + 2;
				break;
			}
			else
				rs2.push_back(line[i1][i]);
		}

		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ' ') {
				last = i + 2;
				break;
			}
			else
				r.push_back(line[i1][i]);
		}

		vector<string> a;

		a.push_back(rs1);
		a.push_back(rs2);
		a.push_back(r);

		return a;
	}


	vector<string> type3(int last, int i1, string line[]) {
		string rs1 = "", rs2 = "", r = "";
		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ',') {
				last = i + 2;
				break;
			}
			else
				rs1.push_back(line[i1][i]);
		}


		bool f = true;
		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == '(') {
				last = i + 1;
				f = false;
				break;
			}
			else
				r.push_back(line[i1][i]);
		}
		if (!f) {
			for (int i = last; i < line[i1].size(); i++) {
				if (line[i1][i] == ')') {
					last = i + 2;
					break;
				}
				else
					rs2.push_back(line[i1][i]);
			}
		}
		else {
			rs2 = r;
			r = "0";
		}

		vector<string> a;


		a.push_back(rs1);
		a.push_back(rs2);
		a.push_back(r);

		return a;
	}


	vector<string> type4(int last, int i1, string line[]) {
		string rs1 = "", r = "";
		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ',') {
				last = i + 2;
				break;
			}
			else
				rs1.push_back(line[i1][i]);
		}



		for (int i = last; i < line[i1].size(); i++) {
			if (line[i1][i] == ' ') {
				last = i + 2;
				break;
			}
			else
				r.push_back(line[i1][i]);
		}


		vector<string> a;


		a.push_back(rs1);

		a.push_back(r);

		return a;
	}



	map<int, string> Rinst() {
		return instructions;
	}



	void binaryGenerate(string line[], int n) {
		map<string, string> registers;
		int ar = 0;
		int addr = -1;

		for (int i = 0; i < 32; i++) {
			string rv = bitset<5> (i).to_string();
			string ii = to_string(i);
			registers["r" + ii] = rv;


		}

		for (int i1 = 0; i1 < n; i1++) {
			string op = "";
			int last = 0;
			bool p = true;
			for (int i = 0; i < line[i1].size(); i++) {
				if (line[i1][i] == ' ' && !p) {
					last = i + 1;
					break;
				}
				else {
					p = false;
					op.push_back(line[i1][i]);
				}
			}

			if (op[op.size() - 1] == ':') {
				// ANMOL TEZ MT CHL

				label[op.substr(0, op.size() - 1)] = i1;


			}
		}

		for (int i1 = 0; i1 < n; i1++) {
			string op = "";
			int last = 0;
			bool p = true;
			for (int i = 0; i < line[i1].size(); i++) {
				if (line[i1][i] == ' ' && !p) {
					last = i + 1;
					break;
				}
				else if (line[i1][i] != ' ') {
					p = false;
					op.push_back(line[i1][i]);
				}
			}
			//deb1(op, i1);

			if (op[op.size() - 1] == ':' && i1 + 1 < n && line[i1 + 1][0] == ' ') {
				int j = i1 + 1;
				int cnt = addr ;
				//int last = 0;
				//	int y = 3;
				while (true) {
					bool p1 = true;
					//cout << "pgkiglti" << endn;
					string op1 = "";
					for (int i = 0; i < line[j].size(); i++) {
						if (line[j][i] == ' ' && !p1) {
							//last = i + 1;
							break;
						}
						else if (line[j][i] != ' ') {
							p1 = false;
							op1.push_back(line[j][i]);
						}
					}
					//deb(op1);
					cnt++;
					j++;
					//deb(line[j]);
					if (op1 == "JALR")
						break;

				}
				int caddr = addr + 1;
				int start = caddr * 4;
				int end = cnt * 4;
				procedure[op.substr(0, op.size() - 1)] = {start, end};
				i1 = j;

				//	deb1(start, end);





			}
		}


		for (int i1 = 0; i1 < n; i1++) {

			string op = "";
			int last = 0;
			bool p = true;
			for (int i = 0; i < line[i1].size(); i++) {
				if (line[i1][i] == ' ' && !p) {
					last = i + 1;
					break;
				}
				else if (line[i1][i] != ' ') {
					p = false;
					op.push_back(line[i1][i]);
				}
			}
			//deb(op);
			if (op[op.size() - 1] == ':' && i1 + 1 < n && line[i1 + 1][0] == ' ') {
				continue;
			}
			else {
				addr++;

				if (op[op.size() - 1] == ':') {
					op = "";
					bool p = true;
					for (int i = last; i < line[i1].size(); i++) {
						if (line[i1][i] == ' ' && !p) {
							last = i + 1;
							break;
						}
						else if (line[i1][i] != ' ') {
							p = false;
							op.push_back(line[i1][i]);
						}
					}

				}

				int address = addr * 4;

				if (op == "ADD") {
					string rs1 = "", rs2 = "", rd = "";
					vector<string> a = type1(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					rs2 = registers[a[2]];


					string ans = add(rs1, rs2, rd);
					instructions[address] = ans;

				}
				else if (op == "ADDI") {
					string rs1 = "", rd = "";

					vector<string> a = type2(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					int val = stoi(a[2]);


					string ans = addi(rs1, val, rd);
					instructions[address] = ans;

				}
				else if (op == "SUB") {
					string rs1 = "", rs2 = "", rd = "";
					vector<string> a = type1(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					rs2 = registers[a[2]];


					string ans = sub(rs1, rs2, rd);
					instructions[address] = ans;


				}
				else if (op == "LW") {
					string rs1 = "", rd = "";

					vector<string> a = type3(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					int val = stoi(a[2]);


					string ans = lw(rs1, val, rd);
					instructions[address] = ans;

				}
				else if (op == "SW") {
					string rs1 = "", rd = "";

					vector<string> a = type3(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					int val = stoi(a[2]);


					string ans = sw(rs1, val, rd);
					instructions[address] = ans;

				}
				else if (op == "JALR") {
					string rd = "r31";
					string ra = to_string(ar);
					string rs1 = "";
					for (int i = last; i < line[i1].size(); i++) {
						if (line[i1][i] == ',') {
							last = i + 2;
							break;
						}
						else
							rs1.push_back(line[i1][i]);
					}


					string ans = jalr(registers[rs1], registers[rd]);
					instructions[address] = ans;




				}
				else if (op == "JAL") {
					ar = i1 + 1;
					string rd = "", r = "";

					vector<string> a = type4(last, i1, line);
					rd = registers[a[0]];
					//r = registers[a[1]];
					//int val = stoi(a[2]);


					string ans = jal(rd, r);
					instructions[address] = ans;




				}
				else if (op == "BEQ") {
					string rs1 = "", rs2 = "";
					vector<string> a = type2(last, i1, line);
					rs1 = registers[a[0]];
					rs2 = registers[a[1]];
					//deb(a[2]);

					string ans = beq(rs1, rs2, i1, a[2]);
					instructions[address] = ans;


				}
				else if (op == "BNE") {
					string rs1 = "", rs2 = "";
					vector<string> a = type2(last, i1, line);
					rs1 = registers[a[0]];
					rs2 = registers[a[1]];

					string ans = bne(rs1, rs2, i1, a[2]);
					instructions[address] = ans;

				}
				else if (op == "BLT") {
					string rs1 = "", rs2 = "";
					vector<string> a = type2(last, i1, line);
					rs1 = registers[a[0]];
					rs2 = registers[a[1]];

					string ans = blt(rs1, rs2, i1, a[2]);
					instructions[address] = ans;

				}
				else if (op == "BGE") {
					string rs1 = "", rs2 = "";
					vector<string> a = type2(last, i1, line);
					rs1 = registers[a[0]];
					rs2 = registers[a[1]];

					string ans = bge(rs1, rs2, i1, a[2]);
					instructions[address] = ans;

				}
				else if (op == "LUI") {
					string rs1 = "";

					vector<string> a = type3(last, i1, line);

					rs1 = registers[a[0]];
					int val = stoi(a[1]);


					string ans = lui(rs1, val);
					instructions[address] = ans;

				}
				else if (op == "AND") {
					string rs1 = "", rs2 = "", rd = "";
					vector<string> a = type1(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					rs2 = registers[a[2]];


					string ans = annd(rs1, rs2, rd);
					instructions[address] = ans;

				}
				else if (op == "OR") {
					string rs1 = "", rs2 = "", rd = "";
					vector<string> a = type1(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					rs2 = registers[a[2]];


					string ans = oor(rs1, rs2, rd);
					instructions[address] = ans;

				}
				else if (op == "XOR") {
					string rs1 = "", rs2 = "", rd = "";
					vector<string> a = type1(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					rs2 = registers[a[2]];


					string ans = xorr(rs1, rs2, rd);
					instructions[address] = ans;

				}
				else if (op == "SLL") {
					string rs1 = "", rs2 = "", rd = "";
					vector<string> a = type1(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					rs2 = registers[a[2]];


					string ans = sll(rs1, rs2, rd);
					instructions[address] = ans;

				}
				else if (op == "SRA") {
					string rs1 = "", rs2 = "", rd = "";
					vector<string> a = type1(last, i1, line);
					rd = registers[a[0]];
					rs1 = registers[a[1]];
					rs2 = registers[a[2]];


					string ans = sra(rs1, rs2, rd);
					instructions[address] = ans;

				}
				//	deb1(op, addr);
			}
		}

	}

};


// int main() {
// 	fast_cin();
// 	Assembler assembler;
// 	int n = 0;

// 	freopen("input.txt", "r", stdin);
// 	freopen("binary.txt", "w", stdout);



// 	vector<string> lines;
// 	string str;
// 	while (getline(cin, str)) {
// 		n++;
// 		lines.push_back(str);
// 		//cout << str << endn;
// 	}
// 	string line[n];
// 	for (int i = 0; i < n; i++) {
// 		line[i] = lines[i];
// 	}


// 	assembler.binaryGenerate(line, n);
// 	map<int, string> instructions = assembler.Rinst();

// 	for (auto x : instructions) {
// 		cout <<  x.second << endn;
// 		//cout << 1 << endn;
// 	}






// 	return 0;
// }