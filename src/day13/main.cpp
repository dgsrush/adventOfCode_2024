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

using std::cout;
using std::endl;
using std::string;
using std::set;
using std::vector;
using std::unordered_map;
using std::stack;

typedef long long llong;
typedef long double ld;

class Button
{
public:
	Button() : x(0), y(0) {}
	llong x, y;
};

class Machine
{
public:
	Machine(llong ax, llong ay, llong bx, llong by, llong xx, llong yy) : x(xx), y(yy)
	{
		a.x = ax; a.y = ay;
		b.x = bx; b.y = by;
	}
	void print()
	{
		cout << "*****" << endl;
		cout << " A:" << a.x << " " << a.y << endl;
		cout << " B:" << b.x << " " << b.y << endl;
		cout << " P:" <<   x << " " <<   y << endl;
	}
	Button a, b;
	llong x, y;
};

vector<Machine> machines;

void readInput()
{
	ReadFile inf("input.txt");

	string delims = "PrizeButonAB: +,XY=";
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;

		vector<string> ll;
		StrUtils::tokenize(ss, delims, ll);
		llong ax = std::stoull(ll[0]);
		llong ay = std::stoull(ll[1]);

		inf.readLine(ss);
		if(ss.empty()) continue;
		ll.clear();
		StrUtils::tokenize(ss, delims, ll);
		llong bx = std::stoull(ll[0]);
		llong by = std::stoull(ll[1]);

		inf.readLine(ss);
		if(ss.empty()) continue;
		ll.clear();
		StrUtils::tokenize(ss, delims, ll);
		llong x = std::stoull(ll[0]);
		llong y = std::stoull(ll[1]);

		machines.emplace_back(ax, ay, bx, by, x, y);
	}
	inf.close();
}

llong calc(Machine m)
{
	bool fnd = false;
	llong min = std::numeric_limits<long long>::max();

	for(llong a = 0; a < 100; a++)
	{
		for(llong b = 0; b < 100; b++)
		{
			llong xx = a * m.a.x + b * m.b.x;
			llong yy = a * m.a.y + b * m.b.y;
			if(xx == m.x && yy == m.y)
			{
				fnd = true;
				llong cst = a * 3 + b;
				if(cst < min) min = cst;
			}
		}
	}

	if(!fnd) return -1;
	return min;
}

void part1()
{
	readInput();
	llong answer1 = 0;
	for(Machine m : machines)
	{
		llong a = calc(m);
		if(a >= 0) answer1 += a;
	}
	cout << "PART1 answer = " << answer1 << endl;
}

ld round(ld var)
{
    ld value = (long long)(var * 100 + .5);
    return (ld)value / 100;
}

ld calcP2(Machine m)
{
	ld mbx = m.b.x;
	ld may = m.a.y;
	ld max = m.a.x;
	ld mby = m.b.y;
	ld my = m.y;
	ld mx = m.x;
	ld a = (mbx / (mbx * may - max * mby) * my) - (mby / (mbx * may - max * mby) * mx);
	ld b = (mx - max * a) / mbx;

	a = round(a);
	b = round(b);
	ld intPart;
    ld fracPart = modfl(a, &intPart);
    if(fracPart != 0.0) return -1;
    fracPart = modfl(b, &intPart);
    if(fracPart != 0.0) return -1;

	ld xx = a * max + b * mbx;
	ld yy = a * may + b * mby;
	if((llong)xx == (llong)mx && (llong)yy == (llong)my)
	{
		ld cst = a * 3.0 + b;
		return cst;
	}

	return -1;
}

void part2()
{
	ld answer2 = 0;
	for(Machine m : machines)
	{
		m.x += 10000000000000;
		m.y += 10000000000000;
		ld a = calcP2(m);
		if(a > 0)
			answer2 += a;
	}
	cout << std::fixed << "PART2 answer = " << answer2 << endl;
}

int main()
{
	part1();
	part2();
	return 0;
}
