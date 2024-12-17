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

typedef enum Dir { N,S,E,W } Dir;

class Pos
{
public:
	Pos() : x(0), y(0), dir(Dir::E), score(0) {}
	Pos(int xx, int yy, Dir d, int scr, vector<Pos> hist) : x(xx), y(yy), dir(d), score(scr)
	{
		if(!hist.empty())
		{
			for(Pos h : hist)
				history.push_back(h);
		}
		Pos p;
		p.x = xx;
		p.y = yy;
		history.push_back(p);
	}
	Pos(int xx, int yy, Dir d, int scr) : x(xx), y(yy), dir(d), score(scr)
	{
		Pos p;
		p.x = xx;
		p.y = yy;
		history.push_back(p);
	}
	void print()
	{
		char sdir = 'N';
		if(dir == Dir::S) sdir = 'S';
		else if(dir == Dir::E) sdir = 'E';
		else if(dir == Dir::W) sdir = 'W';
		cout << "Pos: x=" << x << " y=" << y << " dir=" << sdir << " scr=" << score << endl;
	}
	void printHistory()
	{
		cout << "History:" << endl;
		for(Pos p : history)
			p.print();
		cout << "End History" << endl;
	}
	void addCount(int score, set<string> &count)
	{
		for(Pos h : history)
			count.emplace(std::to_string(score) + ":" + std::to_string(h.x) + ":" + std::to_string(h.y));
	}
	int x, y;
	Dir dir;
	int score;
	vector<Pos> history;
};

vector<string> grid;
int rowcnt = 0;
int colcnt = 0;
Pos start, end;
queue<Pos> todo;

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

unordered_map<string, int> visited;

void compute()
{
	readInput();
	int answer1 = 999999999;
	set<string> count;

	todo.emplace(start.x, start.y, Dir::E, 0);

	while(!todo.empty())
	{
		Pos cur = todo.front();
		todo.pop();

		string key = std::to_string(cur.x) + ":" + std::to_string(cur.y) + ":" + std::to_string(cur.dir);
		if(visited.count(key) == 1)
		{
			if(cur.score > visited[key])
				continue;
		}
		visited.emplace(key, cur.score);

		if(cur.x == end.x && cur.y == end.y)
		{
			cur.addCount(cur.score, count);
			if(cur.score < answer1) answer1 = cur.score;
			continue;
		}

		if(cur.dir == Dir::E)
		{
			if(!isWall(cur.x+1, cur.y))
			{
				todo.emplace(cur.x+1, cur.y, Dir::E, cur.score+1, cur.history);
			}
			if(!isWall(cur.x, cur.y+1))
			{
				todo.emplace(cur.x, cur.y+1, Dir::S, cur.score+1001, cur.history);
			}
			if(!isWall(cur.x, cur.y-1))
			{
				todo.emplace(cur.x, cur.y-1, Dir::N, cur.score+1001, cur.history);
			}
		}
		else if(cur.dir == Dir::N)
		{
			if(!isWall(cur.x+1, cur.y))
			{
				todo.emplace(cur.x+1, cur.y, Dir::E, cur.score+1001, cur.history);
			}
			if(!isWall(cur.x-1, cur.y))
			{
				todo.emplace(cur.x-1, cur.y, Dir::W, cur.score+1001, cur.history);
			}
			if(!isWall(cur.x, cur.y-1))
			{
				todo.emplace(cur.x, cur.y-1, Dir::N, cur.score+1, cur.history);
			}
		}
		else if(cur.dir == Dir::W)
		{
			if(!isWall(cur.x-1, cur.y))
			{
				todo.emplace(cur.x-1, cur.y, Dir::W, cur.score+1, cur.history);
			}
			if(!isWall(cur.x, cur.y+1))
			{
				todo.emplace(cur.x, cur.y+1, Dir::S, cur.score+1001, cur.history);
			}
			if(!isWall(cur.x, cur.y-1))
			{
				todo.emplace(cur.x, cur.y-1, Dir::N, cur.score+1001, cur.history);
			}
		}
		else if(cur.dir == Dir::S)
		{
			if(!isWall(cur.x+1, cur.y))
			{
				todo.emplace(cur.x+1, cur.y, Dir::E, cur.score+1001, cur.history);
			}
			if(!isWall(cur.x-1, cur.y))
			{
				todo.emplace(cur.x-1, cur.y, Dir::W, cur.score+1001, cur.history);
			}
			if(!isWall(cur.x, cur.y+1))
			{
				todo.emplace(cur.x, cur.y+1, Dir::S, cur.score+1, cur.history);
			}
		}
	}

	cout << "PART1 answer = " << answer1 << endl;

	string sanswer = std::to_string(answer1) + ":";
	int answer2 = 0;
	for(set<string>::iterator it = count.begin(); it != count.end(); it++)
	{
    	if(StrUtils::startsWith(*it, sanswer))
			answer2++;
	}
	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	compute();
	return 0;
}
