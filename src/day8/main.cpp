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

vector<string> grid;
set<string> antinode;
set<char> done;
int rowcnt = 0;
int colcnt = 0;

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

void printGrid()
{
	for(string g : grid)
		cout << g << endl;
}

bool inGrid(int r, int c)
{
	if(r < 0 || r >= rowcnt) return false;
	if(c < 0 || c >= colcnt) return false;
	return true;
}

void doPart1(int rr, int cc, char ch)
{
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			if(rr == r && cc == c) continue;
			if(ch == grid[r][c])
			{
				int sy = rr - r;
				int sx = cc - c;
				int rsy = -1 * sy;
				int rsx = -1 * sx;

				int y1 = rr + sy;
				int x1 = cc + sx;
				int y2 = r + rsy;
				int x2 = c + rsx;

				if(inGrid(y1, x1)) antinode.insert(std::to_string(y1)+ ":" + std::to_string(x1));
				if(inGrid(y2, x2)) antinode.insert(std::to_string(y2)+ ":" + std::to_string(x2));
			}
		}
	}
}

void fillLine(int r, int c, int sy, int sx)
{
	antinode.insert(std::to_string(r)+ ":" + std::to_string(c));
	int y = r + sy;
	int x = c + sx;
	if(inGrid(y, x))
	{
		antinode.insert(std::to_string(y)+ ":" + std::to_string(x));
		fillLine(y, x, sy, sx);
	}
}

void doPart2(int rr, int cc, char ch)
{
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			if(rr == r && cc == c) continue;
			if(ch == grid[r][c])
			{
				int sy = rr - r;
				int sx = cc - c;
				int rsy = -1 * sy;
				int rsx = -1 * sx;
				fillLine(rr, cc, sy, sx);
				fillLine(r, c, rsy, rsx);
			}
		}
	}
}

void calc(int rr, int cc, char ch, int part)
{
	done.insert(ch);
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			if(rr == r && cc == c) continue;
			if(ch == grid[r][c])
			{
				if(part == 1)
					doPart1(r, c, ch);
				else
					doPart2(r, c, ch);
			}
		}
	}
}

void part1()
{
	readInput();
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			char ch = grid[r][c];
			if(ch != '.' && done.count(ch) == 0)
				calc(r, c, ch, 1);
		}
	}

	int answer1 = antinode.size();
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	readInput();
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			char ch = grid[r][c];
			if(ch != '.' && done.count(ch) == 0)
				calc(r, c, ch, 2);
		}
	}

	int answer2 = antinode.size();
	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	part1();

	grid.clear();
	antinode.clear();
	done.clear();
	rowcnt = 0;
	colcnt = 0;

	part2();
	return 0;
}
