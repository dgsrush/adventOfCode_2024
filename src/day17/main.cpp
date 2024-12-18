#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<limits>
#include<cmath>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;

unsigned long long RA = 0, RB = 0, RC = 0;
vector<unsigned long long> prog;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	inf.readLine(ss);
	vector<string> ll;
	StrUtils::tokenize(ss, " :", ll);
	RA = std::stoi(ll[2]);

	inf.readLine(ss);
	ll.clear();
	StrUtils::tokenize(ss, " :", ll);
	RB = std::stoi(ll[2]);

	inf.readLine(ss);
	ll.clear();
	StrUtils::tokenize(ss, " :", ll);
	RC = std::stoi(ll[2]);

	inf.readLine(ss);

	inf.readLine(ss);
	ll.clear();
	StrUtils::tokenize(ss, " :,", ll);
	for(int i = 1; i < ll.size(); i++)
		prog.push_back(std::stoi(ll[i]));

	inf.close();
}

unordered_map<long double, long double> powCache;
unordered_map<long double, long double>::const_iterator it;

long double mypow(long double operand)
{
	static long double two = 2.0;

	it = powCache.find(operand);
	if(it == powCache.end())
	{
		long double lg = std::pow(two, operand);
		powCache[operand] = lg;
		return lg;
	}
	else
		return it->second;
}

void calc(vector<unsigned long long> &output, bool part2 = false)
{
	int outcnt = 0;
	for(int i = 0; i < prog.size();)
	{
		unsigned long long opcode = prog[i];
		unsigned long long operand = prog[i+1];

		//cout << "i: " << i << endl;
		//cout << "opc: " << opcode << " opr: " << operand << endl;

		if(opcode == 0)
		{
			if(operand == 4) operand = RA;
			else if(operand == 5) operand = RB;
			else if(operand == 6) operand = RC;
			//RA = (long double)RA / std::pow(two, (long double)operand);
			RA = (long double)RA / mypow(operand);
			i += 2;
		}
		else if(opcode == 1)
		{
			RB = RB ^ operand;
			i += 2;
		}
		else if(opcode == 2)
		{
			if(operand == 4) operand = RA;
			else if(operand == 5) operand = RB;
			else if(operand == 6) operand = RC;
			//RB = operand % 8;
			RB = operand & 7;
			i += 2;
		}
		else if(opcode == 3)
		{
			if(RA != 0)
				i = operand;
			else
				i += 2;
		}
		else if(opcode == 4)
		{
			RB =  RB ^ RC;
			i += 2;
		}
		else if(opcode == 5) //out
		{
			if(operand == 4) operand = RA;
			else if(operand == 5) operand = RB;
			else if(operand == 6) operand = RC;
			//unsigned long long v = operand % 8;
			unsigned long long v = operand & 7;
			output.push_back(v);
			i += 2;

			if(part2)
			{
				if(v != prog[outcnt])
				{
					output[0] = -1;
					return;
				}
				outcnt++;
			}
		}
		else if(opcode == 6)
		{
			if(operand == 4) operand = RA;
			else if(operand == 5) operand = RB;
			else if(operand == 6) operand = RC;
			//RB = (long double)RA / std::pow(two, (long double)operand);
			RB = (long double)RA / mypow(operand);
			i += 2;
		}
		else if(opcode == 7)
		{
			if(operand == 4) operand = RA;
			else if(operand == 5) operand = RB;
			else if(operand == 6) operand = RC;
			//RC = (long double)RA / std::pow(two, (long double)operand);
			RC = (long double)RA / mypow(operand);
			i += 2;
		}
	}
}

int main()
{
	readInput();

	vector<unsigned long long> output;
	calc(output);
	cout << "PART1 answer = "; //7,4,2,5,1,4,6,0,4
	for(unsigned long long v : output)
		cout << v << ",";
	cout << endl;

	return 0;
}
