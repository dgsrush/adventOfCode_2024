#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<unordered_map>
#include<limits>
#include<cmath>
#include<queue>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;
using std::unordered_map;
using std::queue;

class Pos
{
public:
	Pos() : x(0), y(0), score(0) {}

	Pos(int xx, int yy, int scr) : x(xx), y(yy), score(scr)
	{
		Pos p;
		p.x = xx;
		p.y = yy;
	}

	void print() { cout << "Pos: x=" << x << " y=" << y << " scr=" << score << endl; }

	int x, y;
	int score;
};

vector<string> grid;
int rowcnt = 0;
int colcnt = 0;
Pos start, end;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	rowcnt = 0;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		grid.push_back(ss);
		for(int i = 0; i < ss.length(); i++)
		{
			if(ss[i] == 'S') { start.x = i; start.y = rowcnt; }
			else if(ss[i] == 'E') { end.x = i; end.y = rowcnt; }
		}
		rowcnt++;
	}
	inf.close();
	colcnt = grid[0].length();
	grid[start.y][start.x] = '.';
	grid[end.y][end.x] = '.';
}

void printGrid()
{
	for(int y = 0; y < rowcnt; y++)
	{
		for(int x = 0; x < colcnt; x++)
		{
			cout << grid[y][x];
		}
		cout << endl;
	}
}

char getCell(int x, int y)
{
	if(x < 0 || x >= rowcnt) return ' ';
	if(y < 0 || y >= colcnt) return ' ';
	return grid[y][x];
}

bool isWall(int x, int y)
{
	if(getCell(x, y) == '#') return true;
	return false;
}

bool isPath(int x, int y)
{
	if(getCell(x, y) == '.') return true;
	return false;
}

int compute(int wallx, int wally, int pathx, int pathy)
{
	int ans = 999999999;
	queue<Pos> todo;
	unordered_map<string, int> visited;

	todo.emplace(start.x, start.y, 0);

	bool doOnce = false;

	while(!todo.empty())
	{
		Pos cur = todo.front();
		todo.pop();

		string key = std::to_string(cur.x) + ":" + std::to_string(cur.y);
		if(visited.count(key) == 1)
		{
			if(cur.score > visited[key])
				continue;
		}
		visited.emplace(key, cur.score);

		if(cur.x == end.x && cur.y == end.y)
		{
			if(cur.score < ans) ans = cur.score;
			continue;
		}

		bool fix = false;
		if(cur.x == pathx && cur.y == pathy && doOnce == false)
		{
			grid[wally][wallx] = '.';
			fix = true;
			doOnce = true;
		}

		if(!isWall(cur.x+1, cur.y))
			todo.emplace(cur.x+1, cur.y, cur.score+1);
		if(!isWall(cur.x-1, cur.y))
			todo.emplace(cur.x-1, cur.y, cur.score+1);
		if(!isWall(cur.x, cur.y+1))
			todo.emplace(cur.x, cur.y+1, cur.score+1);
		if(!isWall(cur.x, cur.y-1))
			todo.emplace(cur.x, cur.y-1, cur.score+1);

		if(fix)
			grid[wally][wallx] = '#';
	}

	return ans;
}

int main()
{
	readInput();
	//printGrid();

	int cnt = compute(-1, -1, -1, -1);
	int answer1 = 0;
	int target = 99;

	for(int y = 1; y < rowcnt-1; y++)
	{
		for(int x = 1; x < colcnt-1; x++)
		{
			if(isWall(x, y))
			{
				//cout << "y: " << y << " x:" << x << endl;
				if(isPath(x-1, y))
				{
					int cc = compute(x, y, x-1, y);
					if(cc < cnt)
					{
						if((cnt - cc) > target) answer1++;
					}
				}
				if(isPath(x+1, y))
				{
					int cc = compute(x, y, x+1, y);
					if(cc < cnt)
					{
						if((cnt - cc) > target) answer1++;
					}
				}
				if(isPath(x, y-1))
				{
					int cc = compute(x, y, x, y-1);
					if(cc < cnt)
					{
						if((cnt - cc) > target) answer1++;
					}
				}
				if(isPath(x, y+1))
				{
					int cc = compute(x, y, x, y+1);
					if(cc < cnt)
					{
						if((cnt - cc) > target) answer1++;
					}
				}
			}
		}
	}

	cout << "PART1 answer = " << answer1 << endl;

	return 0;
}
