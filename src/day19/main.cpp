#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;

set<string> patterns;
vector<string> designs;
map<string, unsigned long long> cache;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	inf.readLine(ss);
	StrUtils::tokenize(ss, ", ", patterns);
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		designs.push_back(ss);
	}
	inf.close();
}

bool isOkP1(string design, set<string> &patterns)
{
	if(patterns.count(design) == 1) return true;
	for(string pattern : patterns)
	{
		if(StrUtils::startsWith(design, pattern))
		{
			int len = pattern.length();
			string des = design.substr(len);
			if(isOkP1(des, patterns)) return true;
		}
	}
	return false;
}

unsigned long long isOkP2(string design, set<string> &patterns, string pad)
{
	if(cache.count(design) == 1) return cache[design];
	if(design.empty()) return 1;

	unsigned long long cnt = 0;
	for(string pattern : patterns)
	{
		if(StrUtils::startsWith(design, pattern))
		{
			//cout << pad << design << endl;
			int len = pattern.length();
			string des = design.substr(len);
			cnt += isOkP2(des, patterns, pad+" ");
		}
	}

	cache[design] = cnt;
	return cnt;
}

int main()
{
	readInput();

	int answer1 = 0;
	for(string design : designs)
	{
		int cnt = 0;
		if(isOkP1(design, patterns)) answer1++;
	}
	cout << "PART1 answer = " << answer1 << endl;

	////////////////////////////////////////

	unsigned long long answer2 = 0;
	for(string design : designs)
	{
		//cout << "=====================" << endl;
		//cout << "DES: " << design << endl;
		answer2 += isOkP2(design, patterns, "");

		//for(std::map<string, unsigned long long>::iterator it = cache.begin(); it != cache.end(); it++)
		//	cout << "   " << it->first << ":" << it->second << endl;
	}
	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
