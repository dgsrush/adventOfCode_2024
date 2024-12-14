#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<unordered_map>
#include<stack>
#include<limits>
#include<cmath>
#include"ReadFile.h"
#include"StrUtils.h"
#include"MyPng.h"

using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;
using std::unordered_map;
using std::stack;

int rowcnt = 103;
int colcnt = 101;

class Vec2
{
public:
	Vec2() : x(0), y(0) {}
	Vec2(int xx, int yy) : x(xx), y(yy) {}
	void print() { cout << x << "," << y; }
	int x, y;
};

class Robot
{
public:
	Robot(int x, int y, int vx, int vy)
	{
		pos.x = x; pos.y = y;
		vel.x = vx; vel.y = vy;
	}

	void print() { cout << "Robot: pos="; pos.print(); cout << " vel="; vel.print(); cout << endl; }

	void calc()
	{
		pos.x += vel.x;
		pos.y += vel.y;
		if(pos.x >= colcnt) pos.x -= colcnt;
		if(pos.y >= rowcnt) pos.y -= rowcnt;
		if(pos.x < 0) pos.x = colcnt + pos.x;
		if(pos.y < 0) pos.y = rowcnt + pos.y;
	}

	int getQuadrant()
	{
		int midx = colcnt / 2;
		int midy = rowcnt / 2;
		if(pos.x < midx && pos.y < midy) return 0;
		if(pos.x < midx && pos.y > midy) return 1;
		if(pos.x > midx && pos.y < midy) return 2;
		if(pos.x > midx && pos.y > midy) return 3;
		return 4;
	}

	Vec2 pos, vel;
};

vector<Robot> robots;

void readInput()
{
	robots.clear();
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		vector<string> tkns;
		StrUtils::tokenize(ss, "p=v,", tkns);
		robots.emplace_back(std::stoi(tkns[0]), std::stoi(tkns[1]), std::stoi(tkns[2]), std::stoi(tkns[3]));
	}
	inf.close();
}

void part1()
{
	readInput();

	for(int i = 0; i < 100; i++)
	{
		for(Robot &r : robots)
			r.calc();
	}

	int quad[] = {0,0,0,0};
	for(Robot &r : robots)
	{
		int q = r.getQuadrant();
		if(q < 4) quad[q]++;
	}
	int answer1 = 1;
	for(int i = 0; i < 4; i++)
	{
		cout << "quad[" << i << "] = "<< quad[i] << endl;
		answer1 *= quad[i];
	}

	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	readInput();

	for(int i = 0; i < 10000; i++)
	{
		dave::PngWrite png(colcnt, rowcnt);

		for(Robot &r : robots)
		{
			r.calc();
			png.setPixel(r.pos.x, r.pos.y, dave::Color::GREEN);
		}

		string fname = "xmasTree" + std::to_string(i+1) + ".png";
		png.writeFile(fname);
	}
}

int main()
{
	part1();
	part2();
	return 0;
}
