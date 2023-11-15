#include <iostream>
#include <string>
#include <map>
#include <limits.h>
#include <set>
#include <queue>
#include "mst.h"
#include "tsp.h"
#include "max_flow.h"

using namespace std;

int main()
{
    cout << "Number of vertices: ";
    int nVertexes;
    cin >> nVertexes;

    WGraph graph(nVertexes);

    cout << "\nAdjacency Matrix of Distances: " << endl;

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

    cout << "Input Graph of Distances:\n"
         << graph.toString() << endl;

    auto mstGraph = mst(graph);

    cout << "\nMST:\n"
         << mstGraph.toString() << endl;

    auto tspAns = tsp(graph, 0);

    cout << "TSP: " << tspAns.first << endl;
    cout << "Recorrido: ";
    for (auto i : tspAns.second)
        cout << i << " ";
    cout << endl;

    WGraph graph2(nVertexes);
    cout << "\nAdjacency Matrix of Max throughput: " << endl;

    for (int i = 0; i < nVertexes; i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < nVertexes; j++)
        {
            int weight;
            cin >> weight;
            if (weight != -1)
            {
                graph2.addEdge(i, j, weight);
            }
        }
    }

    cout << "Input Graph of Max throughput:\n"
         << graph2.toString() << endl;

    auto ans = fordFulkerson(graph2, 0, nVertexes - 1);
    cout << "Max Flow: " << ans.first << endl;

    cout << "Residual Graph: " << endl;
    cout << ans.second.toString() << endl;
    return 0;
}