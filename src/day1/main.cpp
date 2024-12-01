#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"ReadFile.h"

using std::cout;
using std::endl;

void readInput(std::vector<long> &l1, std::vector<long> &l2)
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

long count(long val, std::vector<long> &ll)
{
	long cnt = 0;
	for(long i : ll)
		if(i == val) cnt++;
	return cnt;
}

int main()
{
	std::vector<long> l1, l2;
	readInput(l1, l2);

	long answer1 = 0;
	long answer2 = 0;
	for(long i = 0; i < l1.size(); i++)
	{
		answer1 += abs(l1[i] - l2[i]);;
		answer2 += l1[i] * count(l1[i], l2);
	}
	std::cout << "PART1 answer = " << answer1 << std::endl;
	std::cout << "PART2 answer = " << answer2 << std::endl;

	return 0;
}
