#include <iostream>
#include <string>
#include <map>
#include <limits.h>
#include <set>
#include <queue>
#include "w_graph.h"

using namespace std;

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
    return 0;
}
