#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<unordered_map>
#include<stack>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;
using std::unordered_map;
using std::stack;

typedef unsigned long long ullong;

vector<ullong> s1, s2;
unordered_map<string, ullong> prev;

void printList(vector<ullong> &ll)
{
	for(ullong i : ll)
		cout << i << " ";
	cout << endl;
}

void readInput()
{
	s1.clear();
	s2.clear();
	ReadFile inf("input.txt");
	//ReadFile inf("test_input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		std::vector<std::string> output;
		StrUtils::tokenize(ss, " ", output);
		for(string n : output)
			s1.push_back(std::stoull(n));
	}
	inf.close();
}

bool isEvenDigits(ullong n)
{
	if(n == 0) return false;
	int cnt = 0;
	while(n != 0)
	{
		n /= 10ULL;
		cnt++;
	}
	return (cnt % 2 == 0);
}

void calc(vector<ullong> &li, vector<ullong> &lo)
{
	for(ullong i : li)
	{
		if(i == 0ULL)
			lo.push_back(1);
		else if(isEvenDigits(i))
		{
			string ss = std::to_string(i);
			int ii = ss.length() / 2;
			string s1 = ss.substr(0, ii);
			string s2 = ss.substr(ii);
			lo.push_back(std::stoull(s1));
			lo.push_back(std::stoull(s2));
		}
		else
			lo.push_back(i * 2024ULL);
	}
	li.clear();
}

void part1()
{
	readInput();
	bool flip = true;
	for(int i = 0; i < 25; i++)
	{
		if(flip)
			calc(s1, s2);
		else
			calc(s2, s1);
		flip = !flip;
	}

	ullong answer1 = s1.size();
	if(answer1 == 0) answer1 = s2.size();

	cout << "PART1 answer = " << answer1 << endl; //198089
}

ullong calcP2(ullong val, int level)
{
	string key = std::to_string(level) + ":" + std::to_string(val);
	if(prev.count(key) == 1)
		return prev[key];

	if(level == 0) return 1ULL;
	ullong ret = 0ULL;
	if(val == 0ULL)
		ret += calcP2(1ULL, level-1);
	else if(isEvenDigits(val))
	{
		string ss = std::to_string(val);
		int ii = ss.length() / 2;
		string s1 = ss.substr(0, ii);
		string s2 = ss.substr(ii);
		ret += calcP2(std::stoull(s1), level-1);
		ret += calcP2(std::stoull(s2), level-1);
	}
	else
		ret += calcP2(val * 2024ULL, level-1);

	prev[key] = ret;
	return ret;
}

void part2()
{
	readInput();
	ullong answer2 = 0;
	for(ullong j : s1)
		answer2 += calcP2(j, 75);
	cout << "PART2 answer = " << (ullong)answer2 << endl; //236302670835517
}

int main()
{
	part1();
	part2();
	return 0;
}
