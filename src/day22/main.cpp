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

typedef unsigned long long ullong;

vector<ullong> secrets;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		secrets.push_back(std::stoll(ss));
	}
	inf.close();
}

ullong mix(ullong val, ullong secret) { return val xor secret; }

ullong prune(ullong secret) { return secret % 16777216; }

ullong evolve(ullong secret)
{
	ullong sec = secret * 64;
	sec = mix(sec, secret);
	sec = prune(sec);

	ullong sec2 = sec / 32;
	sec2 = mix(sec2, sec);

	ullong sec3 = sec2 * 2048;
	sec3 = mix(sec3, sec2);
	sec3 = prune(sec3);
	return sec3;
}

int getDigit(ullong n)
{
	string ss = std::to_string(n);
	return std::stoi(ss.substr(ss.length()-1));
}

class pair
{
public:
	pair(int p, int c) : price(p), change(c) {}
	int price;
	int change;
};

class seq
{
public:
	seq(int ss1, int ss2, int ss3, int ss4) : s1(ss1), s2(ss2), s3(ss3), s4(ss4) {}
	string getKey()
	{
		return std::to_string(s1) + ":" + std::to_string(s2) + ":" +
			std::to_string(s3) + ":" + std::to_string(s4);
	}
	void print()
	{
		cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
	}
	int s1, s2, s3, s4;
};

struct seqComp
{
    bool operator()(seq a, seq b) const
    {
        return a.getKey() < b.getKey();
    }
};

int findSeqCost(seq &s, vector<pair> &changes)
{
	int cnt = changes.size() - 3;
	for(int i = 0; i < cnt; i++)
	{
		if(changes[i].change == s.s1
			&& changes[i+1].change == s.s2
			&& changes[i+2].change == s.s3
			&& changes[i+3].change == s.s4)
		{
			return changes[i+3].price;
		}
	}
	return 0;
}

int main()
{
	readInput();
	vector<pair> changes[secrets.size()];

	int ic = 0;
	ullong answer1 = 0;
	for(ullong sec : secrets)
	{
		int prev = getDigit(sec);

		for(int i = 0; i < 2000; i++)
		{
			sec = evolve(sec);
			int newd = getDigit(sec);
			changes[ic].emplace_back(newd, newd-prev);
			prev = newd;
		}
		answer1 += sec;
		ic++;
	}
	cout << "PART1 answer = " << answer1 << endl;

	set<seq, seqComp> todo;
	for(ic = 0; ic < secrets.size(); ic++)
	{
		int cnt = changes[ic].size() - 3;
		for(int i = 0; i < cnt; i++)
			todo.emplace(changes[ic][i].change, changes[ic][i+1].change, changes[ic][i+2].change, changes[ic][i+3].change);
	}

	int answer2 = 0;
	for(seq s : todo)
	{
		int tot = 0;
		for(int ic = 0; ic < secrets.size(); ic++)
			tot += findSeqCost(s, changes[ic]);
		if(tot > answer2) answer2 = tot;
	}

	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
