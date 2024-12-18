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
#include<utility>
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

#define INF 0x3f3f3f3f

char grid[71][71];
int rowcnt = 71;
int colcnt = 71;
typedef std::pair<int,int> Pair;
string cur = "";

void readInput(int stopCnt)
{
	for(int y = 0; y < rowcnt; y++)
		for(int x = 0; x < colcnt; x++)
			grid[y][x] = '.';

	int cnt = 0;
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		vector<string> ll;
		StrUtils::tokenize(ss, ",", ll);
		int x = std::stoi(ll[0]);
		int y = std::stoi(ll[1]);
		grid[y][x] = '#';
		cnt++;
		if(cnt == stopCnt)
		{
			cur = ss;
			break;
		}
	}
	inf.close();
}

char getCell(int x, int y)
{
	if(x < 0 || x >= rowcnt) return ' ';
	if(y < 0 || y >= colcnt) return ' ';
	return grid[y][x];
}

bool isWall(int x, int y)
{
	char c = getCell(x, y);
	if(c == '#' || c == ' ') return true;
	return false;
}

void printGrid()
{
	for(int y = 0; y < rowcnt; y++)
	{
		for(int x = 0; x < colcnt; x++)
			cout << grid[y][x];
		cout << endl;
	}
}

int getPath(vector<Pair> adj[], int V, int src)
{
	std::priority_queue< Pair, vector <Pair> ,std::greater<Pair> > pq;
	vector<int> dist(V, INF);
	pq.push(std::make_pair(0, src));
	dist[src] = 0;

	while(!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		for(auto x : adj[u])
		{
			int v = x.first;
			int weight = x.second;
			if(dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(std::make_pair(dist[v], v));
			}
		}
	}

	return dist[V-1];
}

void addEdge(vector<Pair> adj[], int u, int v, int wt)
{
	adj[u].push_back(std::make_pair(v, wt));
}

void part1()
{
	readInput(1024);
	int V = rowcnt * colcnt;
	vector<Pair> adj[V];
	int u = 0;

	for(int y = 0; y < rowcnt; y++)
	{
		for(int x = 0; x < colcnt; x++)
		{
			if(!isWall(x+1, y  )) addEdge(adj, u, u+1 , 1);
			if(!isWall(x-1, y  )) addEdge(adj, u, u-1 , 1);
			if(!isWall(x  , y+1)) addEdge(adj, u, u+71, 1);
			if(!isWall(x  , y-1)) addEdge(adj, u, u-71, 1);
			u++;
		}
	}

	int answer1 = getPath(adj, V, 0);

	cout << "PART1 answer = " << answer1 << endl;
}

int compute(int stopCnt)
{
	readInput(stopCnt);
	int V = rowcnt * colcnt;
	vector<Pair> adj[V];
	int u = 0;
	for(int y = 0; y < rowcnt; y++)
	{
		for(int x = 0; x < colcnt; x++)
		{
			if(!isWall(x+1, y  )) addEdge(adj, u, u+1 , 1);
			if(!isWall(x-1, y  )) addEdge(adj, u, u-1 , 1);
			if(!isWall(x  , y+1)) addEdge(adj, u, u+71, 1);
			if(!isWall(x  , y-1)) addEdge(adj, u, u-71, 1);
			u++;
		}
	}
	return getPath(adj, V, 0);
}

int main()
{
	part1();

	for(int i = 1024; i < 3450; i++)
	{
		int ans = compute(i);
		if(ans == 1061109567)
		{
			cout << "PART2 answer = " << cur << endl;
			break;
		}
	}
	return 0;
}
