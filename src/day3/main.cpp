#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

void readInput(vector<string> &ll)
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		ll.push_back(ss);
	}
	inf.close();
}

int main()
{
	vector<string> ll;
	readInput(ll);

	long answer1 = 0;
	long answer2 = 0;

	std::regex rx("mul\\([0-9][0-9]?[0-9]?,[0-9][0-9]?[0-9]?\\)");
	std::smatch match;
	bool do2 = true;

	for(string ss : ll)
	{
		while(std::regex_search(ss, match, rx))
		{
			std::string mul = match.str();

			std::string prefix = match.prefix();
			long f1 = prefix.rfind("do()");
			long f2 = prefix.rfind("don't()");
			if(f1 >= 0 && f2 >= 0)
			{
				if(f2 >= f1) do2 = false;
				else if(f1 > f2) do2 = true;
			}
			else if(f1 >= 0)
				do2 = true;
			else if(f2 >= 0)
				do2 = false;

			std::vector<std::string> nums;
			StrUtils::tokenize(mul, "mul(,)", nums);
			long i1 = stol(nums[0]);
			long i2 = stol(nums[1]);

			if(do2) answer2 += (i1 * i2);
			answer1 += (i1 * i2);

			ss = match.suffix().str();
		}
	}

	cout << "PART1 answer = " << answer1 << endl;
	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
