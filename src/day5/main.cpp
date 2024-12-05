#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<set>
#include<algorithm>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::set;
using std::vector;

unordered_map<int, set<int>> before, after;
vector<vector<int>> lists;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	int row = 0;
	while(inf.readLine(ss))
	{
		if(ss.empty()) break;
		vector<string> tokens;
		StrUtils::tokenize(ss, "|", tokens);
		int n1 = stoi(tokens[0]);
		int n2 = stoi(tokens[1]);

		if(before.count(n1) == 0)
		{
			set<int> ss;
			ss.insert(n2);
			before[n1] = ss;
		}
		else
			before[n1].insert(n2);
		if(after.count(n2) == 0)
		{
			set<int> ss;
			ss.insert(n1);
			after[n2] = ss;
		}
		else
			after[n2].insert(n1);
	}
	while(inf.readLine(ss))
	{
		if(ss.empty()) break;
		vector<string> tokens;
		StrUtils::tokenize(ss, ",", tokens);
		vector<int> list;
		for(int i = 0; i < tokens.size(); i++)
			list.push_back(stoi(tokens[i]));
		lists.push_back(list);
	}
	inf.close();
}

bool isOkBefore(int n1, int n2)
{
	if(before.count(n1) == 0) return true;
	if(before[n1].count(n2) == 1) return true;
	return false;
}

bool isOkAfter(int n1, int n2)
{
	if(after.count(n1) == 0) return true;
	if(after[n1].count(n2) == 1) return true;
	return false;
}

bool myComparator(int n1, int n2)
{
	if(before.count(n1) == 1)
	{
		if(before[n1].count(n2) == 1)
			return true;
	}
	if(after.count(n2) == 1)
	{
		if(after[n2].count(n1) == 1)
			return false;
	}
	return false;
}

void sortList(int i)
{
	std::sort(lists[i].begin(), lists[i].end(), myComparator);
}

int main()
{
	readInput();

	long answer1 = 0;
	long answer2 = 0;

	for(int i = 0; i < lists.size(); i++)
	{
		bool good = true;
		int cnt = lists[i].size() - 1;
		for(int j = 0; j < cnt; j++)
		{
			int n1 = lists[i][j];
			int n2 = lists[i][j+1];

			if(!isOkBefore(n1, n2))
			{
				good = false;
				break;
			}
			if(!isOkAfter(n2, n1))
			{
				good = false;
				break;
			}
		}
		if(good)
		{
			int mid = lists[i].size() / 2;
			answer1 += lists[i][mid];
		}
		else
		{
			sortList(i);
			int mid = lists[i].size() / 2;
			answer2 += lists[i][mid];
		}
	}

	cout << "PART1 answer = " << answer1 << endl;
	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
