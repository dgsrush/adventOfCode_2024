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

vector<string> grid;
int rowcnt = 0;
int colcnt = 0;
set<string> done;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		grid.push_back(ss);
	}
	inf.close();
	rowcnt = grid.size();
	colcnt = grid[0].length();
}

char getCell(int r, int c)
{
	if(r < 0 || r >= rowcnt) return ' ';
	if(c < 0 || c >= colcnt) return ' ';
	return grid[r][c];
}

string getKey(int r, int c) { return std::to_string(r) + ":" + std::to_string(c); }

string getKey(string ch, int c) { return ch + ":" + std::to_string(c); }

int countIt(vector<int> &ll)
{
	std::sort(ll.begin(), ll.end());
	int cnt = 1;
	for(int i = 0; i < ll.size() - 1; i++)
	{
		if((ll[i] + 1) != ll[i+1])
			cnt++;
	}
	return cnt;
}

class Cell
{
public:
	Cell(int rr, int cc) : r(rr), c(cc) {}
	int r, c;
};

int calc(char ch, int r, int c, int part)
{
	int fence = 0;
	int cnt = 0;
	int sides = 0;
	stack<Cell> todo;
	set<string> sideSet;
	unordered_map<string, vector<int>> bb;

	todo.emplace(r, c);
	done.emplace(getKey(r, c));

	while(!todo.empty())
	{
		Cell cell = todo.top();
		todo.pop();
		cnt++;

		if(getCell(cell.r-1, cell.c) != ch) //north
		{
			string ky = getKey("N", cell.r);
			if(bb.count(ky) == 0)
			{
				vector<int> ii = { cell.c };
				bb[ky] = ii;
			}
			else
				bb[ky].push_back(cell.c);

			sideSet.emplace(getKey("N", cell.r));
			fence++;
		}
		if(getCell(cell.r+1, cell.c) != ch) //south
		{
			string ky = getKey("S", cell.r);
			if(bb.count(ky) == 0)
			{
				vector<int> ii = { cell.c };
				bb[ky] = ii;
			}
			else
				bb[ky].push_back(cell.c);

			sideSet.emplace(getKey("S", cell.r));
			fence++;
		}
		if(getCell(cell.r, cell.c+1) != ch) //east
		{
			string ky = getKey("E", cell.c);
			if(bb.count(ky) == 0)
			{
				vector<int> ii = { cell.r };
				bb[ky] = ii;
			}
			else
				bb[ky].push_back(cell.r);

			sideSet.emplace(getKey("E", cell.c));
			fence++;
		}
		if(getCell(cell.r, cell.c-1) != ch) //west
		{
			string ky = getKey("W", cell.c);
			if(bb.count(ky) == 0)
			{
				vector<int> ii = { cell.r };
				bb[ky] = ii;
			}
			else
				bb[ky].push_back(cell.r);

			sideSet.emplace(getKey("W", cell.c));
			fence++;
		}

		if(getCell(cell.r-1, cell.c) == ch && done.count(getKey(cell.r-1, cell.c)) == 0)
		{
			todo.emplace(cell.r-1, cell.c);
			done.emplace(getKey(cell.r-1, cell.c));
		}

		if(getCell(cell.r+1, cell.c) == ch && done.count(getKey(cell.r+1, cell.c)) == 0)
		{
			todo.emplace(cell.r+1, cell.c);
			done.emplace(getKey(cell.r+1, cell.c));
		}

		if(getCell(cell.r, cell.c-1) == ch && done.count(getKey(cell.r, cell.c-1)) == 0)
		{
			todo.emplace(cell.r, cell.c-1);
			done.emplace(getKey(cell.r, cell.c-1));
		}

		if(getCell(cell.r, cell.c+1) == ch && done.count(getKey(cell.r, cell.c+1)) == 0)
		{
			todo.emplace(cell.r, cell.c+1);
			done.emplace(getKey(cell.r, cell.c+1));
		}
	}

	if(part == 2)
	{
		for(auto it = bb.begin(); it != bb.end(); it++)
		{
			int cnt = countIt(it->second);
			sides += cnt;
		}

		return cnt * sides;
	}
	return cnt * fence;
}

void part1()
{
	readInput();
	int answer1 = 0;
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			char ch = grid[r][c];
			if(done.count(getKey(r, c)) == 0)
				answer1 += calc(ch, r, c, 1);
		}
	}
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	done.clear();
	int answer2 = 0;
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			char ch = grid[r][c];
			if(done.count(getKey(r, c)) == 0)
				answer2 += calc(ch, r, c, 2);
		}
	}
	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	part1();
	part2();
	return 0;
}
