#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<unordered_map>
#include<map>
#include<stack>
#include<limits>
#include<cmath>
#include<queue>
#include<utility>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;
using std::unordered_map;
using std::map;
using std::stack;
using std::queue;

set<string> all;
set<string> inputs;

void readInput(string fname)
{
	all.clear();
	inputs.clear();

	ReadFile inf(fname);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		vector<string> ll;
		StrUtils::tokenize(ss, "-", ll);
		all.emplace(ll[0]);
		all.emplace(ll[1]);

		vector<string> vsrt;
		vsrt.push_back(ss.substr(0,2));
		vsrt.push_back(ss.substr(3,2));
		std::sort(vsrt.begin(), vsrt.end());
		inputs.emplace(vsrt[0]+vsrt[1]);
	}
	inf.close();
}

void getCombos(string prefix, int size, vector<string> &ll)
{
	if(!prefix.empty() && prefix[0] != 't') return;

	for(string symbol: all)
	{
		if(size == 1)
			ll.push_back(prefix + symbol);
		else
			getCombos(prefix + symbol, size - 1, ll);
	}
}

void getPerms(int st, vector<string> &in, vector<string> &out)
{
	if(st == in.size()) return;
	for(int i = st; i < in.size(); i++)
		out.push_back(in[st-1] + in[i]);
	getPerms(st+1, in, out);
}

void part1()
{
	set<string> out;
	vector<string> ll;
	getCombos("", 3, ll);

	for(string c : ll)
	{
		vector<string> comps;
		for(int i = 0; i < c.length(); i += 2)
			comps.push_back(c.substr(i, 2));
		std::sort(comps.begin(), comps.end());

		vector<string> perms;
		getPerms(1, comps, perms);

		bool fnd = true;
		for(string perm : perms)
		{
			if(inputs.count(perm) != 1)
			{
				fnd = false;
				break;
			}
		}

		if(fnd)
		{
			string cmp = "";
			for(int j = 0; j < comps.size(); j++)
			{
				if(cmp.empty())
					cmp = comps[j];
				else
					cmp += "," + comps[j];
			}
			out.emplace(cmp);
		}
	}

	//for(string o : out)
	//	cout << o << endl;
	int answer1 = out.size();

	cout << "PART1 answer = " << answer1 << endl;
}

int main()
{
	readInput("input.txt");
	part1();
	return 0;
}
