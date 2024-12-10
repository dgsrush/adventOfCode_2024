#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<stack>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;
using std::stack;

int grid[54][54];
int rowcnt = 0;
int colcnt = 0;

int c2i(char c)
{
	char buf[2] = {c,0};
	return atoi(buf);
}

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	rowcnt = 0;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		colcnt = 0;
		for(char c : ss)
		{
			grid[rowcnt][colcnt] = c2i(c);
			colcnt++;
		}
		rowcnt++;
	}
	inf.close();
}

int getCell(int r, int c)
{
	if(r < 0 || r >= rowcnt) return -1;
	if(c < 0 || c >= colcnt) return -1;
	return grid[r][c];
}

class trail
{
public:
	trail(int rr, int cc) : r(rr), c(cc), headr(rr), headc(cc) {}
	trail(int rr, int cc, int hr, int hc) : r(rr), c(cc), headr(hr), headc(hc) {}
	~trail() {}
	string getKey()
	{
		return std::to_string(headr) + ":" + std::to_string(headc) + ":" +
			std::to_string(r) + ":" + std::to_string(c);
	}
	int headr, headc, r, c;
};

stack<trail> todo;
set<string> answerSet;

int main()
{
	readInput();

	int answer1 = 0;
	int answer2 = 0;

	for(int r = 0; r < rowcnt; r++)
		for(int c = 0; c < colcnt; c++)
			if(getCell(r, c) == 0) todo.emplace(r, c);

	while(!todo.empty())
	{
		trail t = todo.top();
		todo.pop();

		int val = getCell(t.r, t.c);
		if(val < 9)
		{
			val++;
			if(getCell(t.r-1, t.c) == val) todo.emplace(t.r-1, t.c, t.headr, t.headc);
			if(getCell(t.r+1, t.c) == val) todo.emplace(t.r+1, t.c, t.headr, t.headc);
			if(getCell(t.r, t.c+1) == val) todo.emplace(t.r, t.c+1, t.headr, t.headc);
			if(getCell(t.r, t.c-1) == val) todo.emplace(t.r, t.c-1, t.headr, t.headc);
		}
		else
		{
			answer2++;
			answerSet.emplace(t.getKey());
		}
	}

	answer1 = answerSet.size();

	cout << "PART1 answer = " << answer1 << endl;
	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
