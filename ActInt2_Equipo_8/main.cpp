#include <iostream>
#include <string>
#include <map>
#include <limits.h>
#include <set>
#include <queue>
#include "w_graph.h"

using namespace std;

bool bfs(WGraph, int, int, int[]);
pair<int, WGraph> fordFulkerson(WGraph, int, int);

int main()
{

    cout << "Number of vertexes: ";
    int nVertexes;
    cin >> nVertexes;

    WGraph graph(nVertexes);

    cout << "\nAdjacency Matrix: " << endl;

    for (int i = 0; i < nVertexes; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < nVertexes; j++)
        {
            int w;
            cin >> w;
            if (w != -1)
            {
                graph.addEdge(i, j, w);
            }
        }
    }

    cout << graph.toString() << endl;


    auto ans = fordFulkerson(graph, 0,  nVertexes - 1);
    cout << "Max Flow: " << ans.first << endl;

    cout << "Residual Graph: " << endl;
    cout << ans.second.toString() << endl;

    WGraph fractions(nVertexes);

    for (int i = 0; i < nVertexes; i++)
    {
        for (int j = 0; j < nVertexes; j++)
        {
            int base = graph.getWeight(i, j);
            int residual = base - ans.second.getWeight(i, j);
            fractions.addEdge(i, j, residual);
        }
    }

    cout << "Fractions: " << endl;
    cout << fractions.toString() << endl;
    return 0;
}

bool bfs(WGraph rGraph, int start, int end, int parent[])
{
    int nVertexes = rGraph.getNumVertices();
    bool visited[nVertexes];
    for (int i = 0; i < rGraph.getNumVertices(); ++i)
        visited[i] = false;
    
    cout << "BFS: " << endl;
    cout << "Start: " << start << endl;
    cout << "End: " << end << endl;

    queue<int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        auto neighbours = rGraph.getNeighboursWithWeight(current);
        cout << "Current: " << current << endl;
        cout << "Neighbours: " << endl;
        for (auto neighbour : neighbours)
        {
            cout << "\t" << neighbour.first << " " << neighbour.second << endl;
        }


        for (auto neighbour : neighbours)
        {
            if (visited[neighbour.first] == false && neighbour.second > 0)
            {
                if (neighbour.first == end)
                {
                    parent[neighbour.first] = current;
                    return true;
                }
                q.push(neighbour.first);
                parent[neighbour.first] = current;
                visited[neighbour.first] = true;
            }
        }
    }
    return false;
}

pair<int, WGraph> fordFulkerson(WGraph graph, int start, int end)
{
    int nVertexes = graph.getNumVertices();
    WGraph rGraph(graph);
    int parent[nVertexes];
    int max_flow = 0;


    while (bfs(rGraph, start, end, parent))
    {
        int path_flow = INT_MAX;
        int current = end;
        while (current != start)
        {
            int u = parent[current];
            path_flow = min(path_flow, rGraph.getWeight(u, current));
            current = parent[current];
        }

        current = end;
        while (current != start)
        {
            int u = parent[current];
            rGraph.setWeight(u, current, rGraph.getWeight(u, current) - path_flow);
            rGraph.setWeight(current, u, rGraph.getWeight(current, u) + path_flow);
            current = parent[current];
        }

        max_flow += path_flow;
    }
    return {max_flow, rGraph};
}