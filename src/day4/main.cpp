#include<iostream>
#include<string>
#include"ReadFile.h"
#include"StrUtils.h"

using std::cout;
using std::endl;
using std::string;

int rowcnt = 0;
int colcnt = 0;
char grid[140][140];

void readInput()
{
	ReadFile inf("input.txt");
	//ReadFile inf("test_input.txt");
	string ss;
	int row = 0;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		int col = 0;
		for(char c : ss)
		{
			grid[row][col] = c;
			col++;
		}
		colcnt = col;
		row++;
	}
	inf.close();
	rowcnt = row;
}

char cell(int r, int c)
{
	if(r < 0 || r >= rowcnt) return ' ';
	if(c < 0 || c >= colcnt) return ' ';
	return grid[r][c];
}

int main()
{
	readInput();

	long answer1 = 0;
	long answer2 = 0;

	for(int r = 0; r < rowcnt; r++)
	{
		for(int c = 0; c < colcnt; c++)
		{
			if(cell(r, c) == 'X')
			{
				if(cell(r+0,c+1) == 'M' && cell(r+0,c+2) == 'A' && cell(r+0,c+3) == 'S') answer1++;
				if(cell(r+1,c+1) == 'M' && cell(r+2,c+2) == 'A' && cell(r+3,c+3) == 'S') answer1++;
				if(cell(r+1,c+0) == 'M' && cell(r+2,c+0) == 'A' && cell(r+3,c+0) == 'S') answer1++;
				if(cell(r+1,c-1) == 'M' && cell(r+2,c-2) == 'A' && cell(r+3,c-3) == 'S') answer1++;
				if(cell(r+0,c-1) == 'M' && cell(r+0,c-2) == 'A' && cell(r+0,c-3) == 'S') answer1++;
				if(cell(r-1,c-1) == 'M' && cell(r-2,c-2) == 'A' && cell(r-3,c-3) == 'S') answer1++;
				if(cell(r-1,c+0) == 'M' && cell(r-2,c-0) == 'A' && cell(r-3,c+0) == 'S') answer1++;
				if(cell(r-1,c+1) == 'M' && cell(r-2,c+2) == 'A' && cell(r-3,c+3) == 'S') answer1++;
			}
			if(cell(r, c) == 'A')
			{
				if(cell(r-1,c-1) == 'M' && cell(r-1,c+1) == 'M' && cell(r+1,c-1) == 'S' && cell(r+1,c+1) == 'S') answer2++;
				if(cell(r-1,c-1) == 'S' && cell(r-1,c+1) == 'M' && cell(r+1,c-1) == 'S' && cell(r+1,c+1) == 'M') answer2++;
				if(cell(r-1,c-1) == 'S' && cell(r-1,c+1) == 'S' && cell(r+1,c-1) == 'M' && cell(r+1,c+1) == 'M') answer2++;
				if(cell(r-1,c-1) == 'M' && cell(r-1,c+1) == 'S' && cell(r+1,c-1) == 'M' && cell(r+1,c+1) == 'S') answer2++;
			}
		}
	}

	cout << "PART1 answer = " << answer1 << endl;
	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
