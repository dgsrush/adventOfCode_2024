#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<cmath>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

map<string, int> values;

class Op
{
public:
	Op(string v1, string v2, string opr, string vo) : var1(v1), var2(v2), op(opr), vout(vo) {}

	bool calc()
	{
		if(values.count(var1) == 0) return false;
		if(values.count(var2) == 0) return false;
		if(op == "AND") values[vout] = values[var1] & values[var2];
		else if(op == "OR") values[vout] = values[var1] | values[var2];
		else if(op == "XOR") values[vout] = values[var1] xor values[var2];
		return true;
	}

	string var1, var2, op, vout;
};

vector<Op> todo;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) break;
		vector<string> vals;
		StrUtils::tokenize(ss, ": ", vals);
		values[vals[0]] = std::stoi(vals[1]);
	}
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		vector<string> ops;
		StrUtils::tokenize(ss, " ->", ops);
		todo.emplace_back(ops[0], ops[2], ops[1], ops[3]);
	}
	inf.close();
}

unsigned long long bin2long(const string &bin)
{
	unsigned long long ret = 0;
	unsigned long long power = 0;
	for(int i = bin.length()-1; i >= 0; i--)
	{
		if(bin[i] == '1') ret += std::pow(2, power);
		power++;
	}
	return ret;
}

void part1()
{
	while(1)
	{
		bool done = true;
		for(Op op : todo)
		{
			if(!op.calc())
				done = false;
		}
		if(done) break;
	}

	string bin = "00000000000000000000000000000000000000000000000000";
	map<string,int>::iterator it;
	for(it = values.begin(); it != values.end(); it++)
	{
		if(it->first[0] == 'z')
		{
			int ii = std::stoi(it->first.substr(1));
			if(it->second) bin[50-ii-1] = '1';
		}
	}

	unsigned long long answer1 = bin2long(bin);
	cout << "PART1 answer = " << answer1 << endl;
}

int main()
{
	readInput();
	part1();
	return 0;
}
