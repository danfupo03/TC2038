#include <iostream>
#include <string>
#include <map>
#include <limits.h>
#include <set>
#include <queue>
#include "Kruskal.h"

using namespace std;

bool bfs(WGraph, int, int, int[]);
pair<int, WGraph> fordFulkerson(WGraph, int, int);
pair<int, vector<char>> TSP(WGraph, int);
int main()
{
    Kruskal kruskal;

    cout << "Number of vertices: ";
    int nVertexes;
    cin >> nVertexes;

    WGraph graph(nVertexes);

    cout << "\nAdjacency Matrix: " << endl;

    for (int i = 0; i < nVertexes; i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < nVertexes; j++)
        {
            int weight;
            cin >> weight;
            if (weight != -1)
            {
                graph.addEdge(i, j, weight);
            }
        }
    }

    cout << "Input Graph:\n"
         << graph.toString() << endl;

    auto mst = kruskal.kruskalMST(graph);

    // Create a new WGraph to represent the MST
    WGraph mstGraph(nVertexes);
    for (const auto &edge : mst)
    {
        int u = edge.second.first;
        int v = edge.second.second;
        int weight = edge.first;
        mstGraph.addEdge(u, v, weight);
        mstGraph.addEdge(v, u, weight); // Assuming an undirected graph
    }

    cout << "\nMST:\n"
         << mstGraph.toString() << endl;

    auto ans = fordFulkerson(graph, 0, nVertexes - 1);
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

    auto tsp = TSP(graph, 0);

    cout << "TSP: " << tsp.first << endl;
    cout << "Recorrido: ";
    for (char vertex : tsp.second)
    {
        cout << vertex << " ";
    }
    cout << endl;

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

pair<int, vector<char>> TSP(WGraph graph, int start)
{
    int nVertexes = graph.getNumVertices();
    int parent[nVertexes];
    int min_cost = 0;
    WGraph mst(graph);
    int current = start;
    int next = start;
    int count = 0;

    vector<char> visited;

    char vertexToLetter[26];
    for (int i = 0; i < 26; ++i)
    {
        vertexToLetter[i] = static_cast<char>('A' + i);
    }

    while (count < nVertexes)
    {
        int min = INT_MAX;
        auto neighbours = mst.getNeighboursWithWeight(current);
        for (auto neighbour : neighbours)
        {
            if (neighbour.second < min)
            {
                min = neighbour.second;
                next = neighbour.first;
            }
        }
        min_cost += min;
        mst.setWeight(current, next, INT_MAX);
        mst.setWeight(next, current, INT_MAX);
        current = next;
        visited.push_back(vertexToLetter[current]);
        count++;
    }
    visited.push_back(vertexToLetter[start]);
    return {min_cost, visited};
}
