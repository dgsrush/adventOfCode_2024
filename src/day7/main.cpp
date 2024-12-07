#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<unordered_map>
#include<vector>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::set;
using std::vector;

class row
{
public:
	row() : res(0) {};
	unsigned long long res;
	vector<unsigned long long> vals;
};

vector<row> rows;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		std::vector<std::string> ll;
		StrUtils::tokenize(ss, ": ", ll);
		row r;
		r.res = std::stoll(ll[0]);
		for(int i = 1; i < ll.size(); i++)
			r.vals.push_back(stoll(ll[i]));
		rows.push_back(r);
	}
	inf.close();
}

void getCombos(string prefix, int size, vector<string> &ll)
{
	static string symbols[] = {"+", "*"};
	for(string symbol: symbols)
	{
		if(size == 1)
			ll.push_back(prefix + symbol);
		else
			getCombos(prefix + symbol, size - 1, ll);
	}
}

void getCombosPart2(string prefix, int size, vector<string> &ll)
{
	static string symbols[] = {"+", "*", "|"};
	for(string symbol: symbols)
	{
		if(size == 1)
			ll.push_back(prefix + symbol);
		else
			getCombosPart2(prefix + symbol, size - 1, ll);
	}
}

void part1()
{
	unsigned long long answer1 = 0;

	for(row r : rows)
	{
		int len = r.vals.size() - 1;

		vector<string> combos;
		getCombos("", len, combos);
		for(string combo : combos)
		{
			unsigned long long bb = r.vals[0];
			for(int i = 1; i < r.vals.size(); i++)
			{
				if(combo[i-1] == '+')
					bb += r.vals[i];
				else
					bb *= r.vals[i];
			}
			if(bb == r.res)
			{
				answer1 += bb;
				break;
			}
		}
	}

	cout << "PART1 answer = " << answer1 << endl;
}

unsigned long long concat(unsigned long long n1, unsigned long long n2)
{
	return stoll(std::to_string(n1) + std::to_string(n2));
}

void part2()
{
	unsigned long long answer2 = 0;

	for(row r : rows)
	{
		int len = r.vals.size() - 1;

		vector<string> combos;
		getCombosPart2("", len, combos);
		for(string combo : combos)
		{
			unsigned long long bb = r.vals[0];
			for(int i = 1; i < r.vals.size(); i++)
			{
				if(combo[i-1] == '+')
					bb += r.vals[i];
				else if(combo[i-1] == '*')
					bb *= r.vals[i];
				else
					bb = concat(bb, r.vals[i]);
			}
			if(bb == r.res)
			{
				answer2 += bb;
				break;
			}
		}
	}

	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	readInput();
	part1();
	part2();
	return 0;
}
