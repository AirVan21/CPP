#include <iostream>
#include <string>
#include <set>
#include <vector> 
#include <stack>
#include <algorithm>

using namespace std;

void findEulerCycle(vector< vector<int> > &graph, vector< vector<int> > &lineGraph)
{
	stack<int> vertexStack;
	vector<int> degree(lineGraph.size());
	vector<int> result;
	for (int i = 0; i < lineGraph.size(); i++)
	{
		degree[i] = lineGraph[i].size();
	}

	// Start node
	vertexStack.push(0);

	while (!vertexStack.empty())
	{
		int node = vertexStack.top();
		
		if (!degree[node])
		{
			result.push_back(node + 1);
			vertexStack.pop();
		}

		for (vector<int>::iterator i = lineGraph[node].begin(); i != lineGraph[node].end(); i++)
		{
			if (graph[node][*i] > 0)
			{
				vertexStack.push(*i);
				graph[node][*i]--;
				graph[*i][node]--;
				degree[node]--;
				degree[*i]--;
				break;
			}
		}
	}
	for (int i = 0; i < result.size() - 1; i++)
	{
		cout << result[i] << " ";
	}
}

void dfs(int node, vector< vector<int> > &graph, vector<bool> &color)
{
	color[node] = true;
	for (vector<int>::iterator i = graph[node].begin(); i != graph[node].end(); i++)
	{
		if (!color[*i])
			dfs(*i, graph, color);
	}
}

bool isConnected(vector< vector<int> > &graph)
{
	vector<bool> colorMarker(graph.size(), false);
	int startNode = 0;
	dfs(startNode, graph, colorMarker);

	for (unsigned int i = 0; i < colorMarker.size(); ++i)
	{
		if (!colorMarker[i])
			return false;
	}

	return true;
}

int main(int argc, char const *argv[])
{
	using namespace std;

	int nVerteces = 0;
	unsigned int nEdges = 0;

	cin >> nVerteces;
	cin >> nEdges;

	int aNode = 0;
	int bNode = 0;

	// Init identity table
	vector< vector<int> > mGraph(nVerteces, vector<int>(nVerteces));
	vector< vector<int> > listGraph(nVerteces);
	for (unsigned int i = 0; i < nEdges; ++i)
	{
		cin >> aNode;
		cin >> bNode;
		mGraph[aNode - 1][bNode - 1] += 1;
		mGraph[bNode - 1][aNode - 1] += 1;
		listGraph[aNode - 1].push_back(bNode - 1);
		listGraph[bNode - 1].push_back(aNode - 1);
	}

	if (!isConnected(listGraph))
	{
		cout << "NONE" << endl;
		return 0;
	}

	for (unsigned int i = 0; i < listGraph.size(); ++i)
	{
		if (listGraph[i].size() % 2 != 0)
		{
			cout << "NONE" << endl;
			return 0;
		}
	}

	findEulerCycle(mGraph, listGraph);

	return 0;
}