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

int x = 0;
int y = 0;
int dir = 0; //0=up 1=right 2=down 3=left
int w = 0;
int h = 0;
vector<string> grid;
int answer1, answer2;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	h = 0;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		grid.push_back(ss);
		w = ss.size();
		for(int i = 0; i < w; i++)
			if(ss[i] == '^') { x = i; y = h; }
		h++;
	}
	inf.close();
}

void printGrid()
{
	for(string ss : grid)
		cout << ss << endl;
	cout << "" << endl;
}

bool inGrid(int yy, int xx)
{
	if(yy < 0 || yy >= h) return false;
	if(xx < 0 || xx >= w) return false;
	return true;
}

char getCell(int yy, int xx)
{
	if(yy < 0 || yy >= h) return ' ';
	if(xx < 0 || xx >= w) return ' ';
	return grid[yy][xx];
}

void rotate()
{
	dir++;
	if(dir == 4) dir = 0;
}

void part1()
{
	readInput();
	answer1 = 1;

	while(inGrid(y, x))
	{
		if(dir == 0) //up
		{
			if(getCell(y-1, x) == '#')
				rotate();
			else
			{
				y--;
				if(inGrid(y, x))
				{
					if(getCell(y, x) == '.') answer1++;
					grid[y][x] = 'X';
				}
			}
		}
		else if(dir == 1) //right
		{
			if(getCell(y, x+1) == '#')
				rotate();
			else
			{
				x++;
				if(inGrid(y, x))
				{
					if(getCell(y, x) == '.') answer1++;
					grid[y][x] = 'X';
				}
			}
		}
		else if(dir == 2) //down
		{
			if(getCell(y+1, x) == '#')
				rotate();
			else
			{
				y++;
				if(inGrid(y, x))
				{
					if(getCell(y, x) == '.') answer1++;
					grid[y][x] = 'X';
				}
			}
		}
		else if(dir == 3) //left
		{
			if(getCell(y, x-1) == '#')
				rotate();
			else
			{
				x--;
				if(inGrid(y, x))
				{
					if(getCell(y, x) == '.') answer1++;
					grid[y][x] = 'X';
				}
			}
		}
	}
}

string createHistory(int y, int x, int dir)
{
	return std::to_string(y) + ":" + std::to_string(x) + ":" + std::to_string(dir);
}

void part2()
{
	answer2 = 0;

	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			grid.clear();
			readInput();
			dir = 0;
			if(y == j && x == i) continue;
			grid[j][i] = '#';

			set<string> history;
			history.insert(createHistory(y, x, dir));

			while(inGrid(y, x))
			{
				if(dir == 0) //up
				{
					if(getCell(y-1, x) == '#')
						rotate();
					else
					{
						y--;
						if(inGrid(y, x))
						{
							string h = createHistory(y, x, dir);
							if(history.count(h) == 1)
							{
								answer2++;
								break;
							}
							history.insert(h);
						}
					}
				}
				else if(dir == 1) //right
				{
					if(getCell(y, x+1) == '#')
						rotate();
					else
					{
						x++;
						if(inGrid(y, x))
						{
							string h = createHistory(y, x, dir);
							if(history.count(h) == 1)
							{
								answer2++;
								break;
							}
							history.insert(h);
						}
					}
				}
				else if(dir == 2) //down
				{
					if(getCell(y+1, x) == '#')
						rotate();
					else
					{
						y++;
						if(inGrid(y, x))
						{
							string h = createHistory(y, x, dir);
							if(history.count(h) == 1)
							{
								answer2++;
								break;
							}
							history.insert(h);
						}
					}
				}
				else if(dir == 3) //left
				{
					if(getCell(y, x-1) == '#')
						rotate();
					else
					{
						x--;
						if(inGrid(y, x))
						{
							string h = createHistory(y, x, dir);
							if(history.count(h) == 1)
							{
								answer2++;
								break;
							}
							history.insert(h);
						}
					}
				}
			}
		}
	}
}

int main()
{
	part1();
	part2();
	cout << "PART1 answer = " << answer1 << endl;
	cout << "PART2 answer = " << answer2 << endl;
	return 0;
}
