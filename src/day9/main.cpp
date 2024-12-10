#include<algorithm>
#include<iostream>
#include<set>
#include<string>
#include<vector>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef unsigned long long ullong;
typedef unsigned long ulong;
typedef long long llong;

class block
{
public:
	block() : id(-1) {}
	block(llong i) : id(i) {}
	~block() {}
	llong getId() { return id; }
	void setId(llong i) { id = i; }
	void setFree() { id = -1; }
	bool isFree() { return (id == -1); }
	void print()
	{
		if(isFree())
			cout << ".";
		else
			cout << id;
	}
private:
	llong id;
};

string inp;
vector<block> data;

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		inp = ss;
	}
	inf.close();
}

int c2i(char c)
{
	char buf[2] = {c, 0};
	return std::stoi(buf);
}

void printList()
{
	for(block b : data)
		b.print();
	cout << endl;
}

long findFree()
{
	static ulong lastFree = 0;
	for(ulong i = lastFree; i < data.size(); i++)
	{
		if(data[i].isFree())
		{
			lastFree = i;
			return i;
		}
	}
	return -1;
}

long findFree(int len)
{
	for(ulong i = 0; i < data.size(); i++)
	{
		if(data[i].isFree())
		{
			if(len == 1) return i;
			bool fnd = true;
			for(ulong j = 1; j < len; j++)
			{
				if((i+j) >= data.size())
				{
					fnd = false;
					break;
				}
				if(!data[i+j].isFree())
				{
					fnd = false;
					break;
				}
			}
			if(fnd) return i;
		}
	}
	return -1;
}

void step1()
{
	bool isFile = true;
	llong id = 0;
	for(char c : inp)
	{
		int n = c2i(c);
		if(isFile)
		{
			for(int i = 0; i < n; i++)
				data.emplace_back(id);
			id++;
		}
		else
		{
			for(int i = 0; i < n; i++)
				data.emplace_back();
		}
		isFile = !isFile;
	}
}

void part1()
{
	ullong answer1 = 0;
	readInput();

	step1();

	for(ulong i = (data.size() - 1); i >= 0; i--)
	{
		if(!data[i].isFree())
		{
			int j = findFree();
			if(j > i) break;
			data[j].setId(data[i].getId());
			data[i].setFree();
		}
	}

	for(ulong i = 0; i < data.size(); i++)
	{
		if(data[i].isFree()) break;
		answer1 += i * data[i].getId();
	}

	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	ullong answer2 = 0;

	step1();

	for(ulong i = (data.size() - 1); i >= 0; i--)
	{
		if(data[i].isFree()) continue;

		llong id = data[i].getId();
		int len = 1;
		while(i > 0 && data[i-1].getId() == id)
		{
			i--;
			len++;
		}

		long f = findFree(len);
		if(f < i && f >= 0)
		{
			for(int j = 0; j < len; j++)
				data[f + j].setId(id);
			for(int j = 0; j < len; j++)
				data[i + j].setFree();
		}

		if(i == 0) break;
	}

	for(ulong i = 0; i < data.size(); i++)
	{
		if(data[i].isFree()) continue;
		answer2 += i * data[i].getId();
	}

	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	part1();
	data.clear();
	part2();
	return 0;
}
