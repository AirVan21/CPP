#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

void dfs(int startNode, std::vector<std::vector<int>> &graph, std::vector<int> &color)
{

	// Color node
	color[startNode] = 1;
	for (vector<int>::iterator node = graph[startNode].begin(); node != graph[startNode].end(); node++)
	{
		if (!color[*node])
		{
			dfs(*node, graph, color);
		}
	}
}

int main()
{
	int nNodes;
	int nEdges;
	cin >> nNodes;
	cin >> nEdges;

	vector<vector<int>> graph(nNodes);
	vector<int> color(nNodes);
	int aNode, bNode;
	
	while (cin >> aNode)
	{
		cin >> bNode;
		graph[aNode - 1].push_back(bNode - 1);
		graph[bNode - 1].push_back(aNode - 1);
	}

	int nConnectComp = 0;

	for (int i = 0; i < graph.size(); i++)
	{
		if (!color[i])
		{
			dfs(i, graph, color);
			nConnectComp++;
		}
	}

	cout << nConnectComp;

	return 0;
}