#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"ReadFile.h"

using std::cout;
using std::endl;
using std::vector;

void readInput(vector<long> &l1, vector<long> &l2)
{
	ReadFile inf("input.txt");
	std::string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		long i1 = std::stoi(ss.substr(0, 5));
		long i2 = std::stoi(ss.substr(8));
		l1.push_back(i1);
		l2.push_back(i2);
	}
	inf.close();
	std::sort(l1.begin(), l1.end());
	std::sort(l2.begin(), l2.end());
}

int main()
{
	vector<long> l1, l2;
	readInput(l1, l2);

	long answer1 = 0;
	long answer2 = 0;
	for(long i = 0; i < l1.size(); i++)
	{
		answer1 += abs(l1[i] - l2[i]);;
		answer2 += l1[i] * std::count(l2.begin(), l2.end(), l1[i]);
	}
	cout << "PART1 answer = " << answer1 << endl;
	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
