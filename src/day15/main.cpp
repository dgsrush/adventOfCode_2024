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

std::map<int,char> grid;
int rowcnt = 0;
int colcnt = 0;
string moves;
int posx = 0;
int posy = 0;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		if(ss[0] == '#')
		{
			for(int i = 0; i < ss.length(); i++)
			{
				if(ss[i] == '@')
				{
					posy = rowcnt;
					posx = i;
					ss[i] = '.';
				}
				grid[rowcnt*100+i] = ss[i];
			}
			colcnt = ss.length();
			rowcnt++;
		}
		else
			moves += ss;
	}
	inf.close();
}

void readInputP2()
{
	rowcnt = 0;
	colcnt = 0;
	posx = 0;
	posy = 0;
	moves.clear();
	grid.clear();

	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		if(ss[0] == '#')
		{
			int ii = 0;
			for(int i = 0; i < ss.length(); i++)
			{
				if(ss[i] == '@')
				{
					posy = rowcnt;
					posx = ii;
					ss[i] = '.';
				}
				if(ss[i] == '#')
				{
					grid[rowcnt*100+ii] = '#';
					grid[rowcnt*100+ii+1] = '#';
				}
				else if(ss[i] == 'O')
				{
					grid[rowcnt*100+ii] = '[';
					grid[rowcnt*100+ii+1] = ']';
				}
				else if(ss[i] == '.')
				{
					grid[rowcnt*100+ii] = '.';
					grid[rowcnt*100+ii+1] = '.';
				}
				ii += 2;
			}
			colcnt = ss.length() * 2;
			rowcnt++;
		}
		else
			moves += ss;
	}
	inf.close();
}

void printGrid()
{
	cout << endl;
	for(int i = 0; i < rowcnt; i++)
	{
		for(int j = 0; j < colcnt; j++)
		{
			if(i == posy && j == posx)
				cout << 'X';
			else
				cout << grid[i*100+j];
		}
		cout << endl;
	}
	cout << endl;
}

void moveLeft()
{
	int newx = posx - 1;
	int gps = posy * 100 + newx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posx = newx;
	else if(ch == 'O')
	{
		int endx = newx;
		while(grid[posy * 100 + (endx-1)] == 'O')
			endx--;
		if(grid[posy * 100 + (endx-1)] == '.')
		{
			for(int x = endx; x <= newx; x++)
			{
				grid[posy * 100 + (x)] = '.';
				grid[posy * 100 + (x-1)] = 'O';
			}
			posx = newx;
		}
	}
}

void moveRight()
{
	int newx = posx + 1;
	int gps = posy * 100 + newx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posx = newx;
	else if(ch == 'O')
	{
		int endx = newx;
		while(grid[posy * 100 + (endx+1)] == 'O')
			endx++;
		if(grid[posy * 100 + (endx+1)] == '.')
		{
			for(int x = endx; x >= newx; x--)
			{
				grid[posy * 100 + (x)] = '.';
				grid[posy * 100 + (x+1)] = 'O';
			}
			posx = newx;
		}
	}
}

void moveDown()
{
	int newy = posy + 1;
	int gps = newy * 100 + posx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posy = newy;
	else if(ch == 'O')
	{
		int endy = newy;
		while(grid[(endy + 1) * 100 + posx] == 'O')
			endy++;
		if(grid[(endy+1) * 100 + posx] == '.')
		{
			for(int y = endy; y >= newy; y--)
			{
				grid[y * 100 + posx] = '.';
				grid[(y+1) * 100 + posx] = 'O';
			}
			posy = newy;
		}
	}
}

void moveUp()
{
	int newy = posy - 1;
	int gps = newy * 100 + posx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posy = newy;
	else if(ch == 'O')
	{
		int endy = newy;
		while(grid[(endy - 1) * 100 + posx] == 'O')
			endy--;
		if(grid[(endy-1) * 100 + posx] == '.')
		{
			for(int y = endy; y <= newy; y++)
			{
				grid[y * 100 + posx] = '.';
				grid[(y-1) * 100 + posx] = 'O';
			}
			posy = newy;
		}
	}
}

class Box
{
public:
	Box(int xx, int yy) : x(xx), y(yy) {}

	void print() { cout << "Box: " << x << " " << y << endl; }

	bool canMoveRight()
	{
		if(grid[y*100+x+2] == '.') return true;
		return false;
	}

	bool canMoveLeft()
	{
		if(grid[y*100+x-1] == '.') return true;
		return false;
	}

	bool isOpen(int xx, int yy)
	{
		if(grid[yy*100+xx] == '#') return false;
		return true;
	}

	bool canMoveDown()
	{
		if(isOpen(x, y+1) && isOpen(x+1, y+1)) return true;
		return false;
	}

	bool canMoveUp()
	{
		if(isOpen(x, y-1) && isOpen(x+1, y-1)) return true;
		return false;
	}

	void moveRight()
	{
		grid[y*100+x] = '.';
		grid[y*100+x+1] = '[';
		grid[y*100+x+2] = ']';
	}

	void moveLeft()
	{
		grid[y*100+x-1] = '[';
		grid[y*100+x] = ']';
		grid[y*100+x+1] = '.';
	}

	void moveDown()
	{
		grid[(y+1)*100+x] = '[';
		grid[(y+1)*100+x+1] = ']';
		grid[y*100+x] = '.';
		grid[y*100+x+1] = '.';
	}

	void moveUp()
	{
		grid[(y-1)*100+x] = '[';
		grid[(y-1)*100+x+1] = ']';
		grid[y*100+x] = '.';
		grid[y*100+x+1] = '.';
	}

	int x, y;
};

void getBoxListToTheRight(int x, int y, vector<Box> &mv)
{
	mv.emplace_back(x, y);
	x += 2;
	char ch = grid[y * 100 + x];
	if(ch == '[')
		getBoxListToTheRight(x, y, mv);
}

void getBoxListToTheLeft(int x, int y, vector<Box> &mv)
{
	mv.emplace_back(x, y);
	x -= 2;
	char ch = grid[y * 100 + x];
	if(ch == '[')
		getBoxListToTheLeft(x, y, mv);
}

void getBoxListDown(int x, int y, vector<Box> &mv)
{
	for(Box b : mv)
		if(b.x == x && b.y == y) return;

	mv.emplace_back(x, y);
	y++;
	char ch1 = grid[y*100+x];
	char ch2 = grid[y*100+x+1];
	if(ch1 == '[' && ch2 == ']')
		getBoxListDown(x, y, mv);
	if(ch1 == ']')
		getBoxListDown(x-1, y, mv);
	if(ch2 == '[')
		getBoxListDown(x+1, y, mv);
}

void getBoxListUp(int x, int y, vector<Box> &mv)
{
	for(Box b : mv)
		if(b.x == x && b.y == y) return;

	mv.emplace_back(x, y);
	y--;
	char ch1 = grid[y*100+x];
	char ch2 = grid[y*100+x+1];
	if(ch1 == '[' && ch2 == ']')
		getBoxListUp(x, y, mv);
	if(ch1 == ']')
		getBoxListUp(x-1, y, mv);
	if(ch2 == '[')
		getBoxListUp(x+1, y, mv);
}

void moveRightP2()
{
	int newx = posx + 1;
	int gps = posy * 100 + newx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posx = newx;
	else if(ch == '[')
	{
		vector<Box> mv;
		getBoxListToTheRight(newx, posy, mv);
		if(mv.back().canMoveRight())
		{
			std::reverse(mv.begin(), mv.end());
			for(Box &b : mv)
				b.moveRight();
			posx = newx;
		}
	}
}

void moveLeftP2()
{
	int newx = posx - 1;
	int gps = posy * 100 + newx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posx = newx;
	else if(ch == ']')
	{
		vector<Box> mv;
		getBoxListToTheLeft(newx-1, posy, mv);
		if(mv.back().canMoveLeft())
		{
			std::reverse(mv.begin(), mv.end());
			for(Box &b : mv)
				b.moveLeft();
			posx = newx;
		}
	}
}

bool boxCompare(Box i, Box j)
{
	if(i.y == j.y) return (i.x < j.x);
	return (i.y < j.y);
}

void moveDownP2()
{
	int newy = posy + 1;
	int gps = newy * 100 + posx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posy = newy;
	else if(ch == '[' || ch == ']')
	{
		int px = posx;
		if(ch == ']') px--;

		vector<Box> mv;
		getBoxListDown(px, newy, mv);
		bool canMove = true;
		for(Box &b : mv)
		{
			if(!b.canMoveDown())
			{
				canMove = false;
				break;
			}
		}
		if(canMove)
		{
			std::sort(mv.begin(), mv.end(), boxCompare);
			std::reverse(mv.begin(), mv.end());
			for(Box &b : mv)
				b.moveDown();
			posy = newy;
		}
	}
}

void moveUpP2()
{
	int newy = posy - 1;
	int gps = newy * 100 + posx;
	char ch = grid[gps];
	if(ch == '#')
		return;
	else if(ch == '.')
		posy = newy;
	else if(ch == '[' || ch == ']')
	{
		int px = posx;
		if(ch == ']') px--;

		vector<Box> mv;
		getBoxListUp(px, newy, mv);
		bool canMove = true;
		for(Box &b : mv)
		{
			if(!b.canMoveUp())
			{
				canMove = false;
				break;
			}
		}
		if(canMove)
		{
			std::sort(mv.begin(), mv.end(), boxCompare);
			for(Box &b : mv)
				b.moveUp();
			posy = newy;
		}
	}
}

void doMove(char move)
{
	if(move == '<') moveLeft();
	else if(move == '>') moveRight();
	else if(move == '^') moveUp();
	else moveDown();
}

void doMoveP2(char move)
{
	if(move == '<') moveLeftP2();
	else if(move == '>') moveRightP2();
	else if(move == '^') moveUpP2();
	else moveDownP2();
}

void part1()
{
	readInput();
	for(int i = 0; i < moves.length(); i++)
		doMove(moves[i]);
	int answer1 = 0;
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			int gps = r * 100 + c;
			if(grid[gps] == 'O')
				answer1 += gps;
		}
	}
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	readInputP2();
	for(int i = 0; i < moves.length(); i++)
		doMoveP2(moves[i]);
	int answer2 = 0;
	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			int gps = r * 100 + c;
			if(grid[gps] == '[')
				answer2 += gps;
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

