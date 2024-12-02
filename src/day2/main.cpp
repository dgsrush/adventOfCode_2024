#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

void readInput(vector<vector<int>> &ll)
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		vector<string> sl;
		vector<int> il;
		StrUtils::tokenize(ss, " ", sl);
		for(string s : sl)
			il.push_back(stoi(s));
		ll.push_back(il);
	}
	inf.close();
}

bool isIncreasing(vector<int> &ll)
{
	int cnt = ll.size() - 1;
	for(int i = 0; i < cnt; i++)
		if(ll[i] >= ll[i+1]) return false;
	return true;
}

bool isDecreasing(vector<int> &ll)
{
	int cnt = ll.size() - 1;
	for(int i = 0; i < cnt; i++)
		if(ll[i] <= ll[i+1]) return false;
	return true;
}

bool isSafe(vector<int> &ll)
{
	if(!isIncreasing(ll) && !isDecreasing(ll)) return false;
	int cnt = ll.size() - 1;
	for(int i = 0; i < cnt; i++)
		if(abs(ll[i] - ll[i+1]) > 3) return false;
	return true;
}

bool isSafeSingleBad(vector<int> &ll)
{
	vector<vector<int>> all;
	for(int i = 0; i < ll.size(); i++)
	{
		vector<int> zz;
		for(int j = 0; j < ll.size(); j++)
		{
			if(i == j) continue;
			zz.push_back(ll[j]);
		}
		all.push_back(zz);
	}
	for(int i = 0; i < all.size(); i++)
		if(isSafe(all[i])) return true;
	return false;
}

int main()
{
	vector<vector<int>> ll;
	readInput(ll);

	int answer1 = 0;
	int answer2 = 0;
	for(int i = 0; i < ll.size(); i++)
	{
		bool safe = isSafe(ll[i]);
		if(safe) answer1++;
		if(safe || isSafeSingleBad(ll[i])) answer2++;
	}
	cout << "PART1 answer = " << answer1 << endl;
	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
