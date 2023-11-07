#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/**
 * @brief Check if it's safe to assign a color to a node.
 *
 * @param index Node index
 * @param graph Adjacency matrix
 * @param color Color assignment for nodes
 * @param c Color to be assigned
 * @return true if it's safe to assign the color, false otherwise
 */
bool isSafe(int index, vector<vector<int>> &graph, vector<int> &color, int c)
{
    for (int i = 0; i < graph.size(); ++i)
    {
        if (graph[index][i] && color[i] == c)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Recursively assign colors to nodes in the graph.
 *
 * @param graph Adjacency matrix
 * @param color Color assignment for nodes
 * @param v Current node index
 * @return true if a valid coloring is found, false otherwise
 */
bool graphColoringUtil(vector<vector<int>> &graph, vector<int> &color, int currNodeIndex)
{
    if (currNodeIndex == graph.size())
    {
        return true;
    }

    for (int c = 0; c <= currNodeIndex; ++c) // Start color index from 0
    {
        if (isSafe(currNodeIndex, graph, color, c))
        {
            color[currNodeIndex] = c;
            if (graphColoringUtil(graph, color, currNodeIndex + 1))
            {
                return true;
            }
            color[currNodeIndex] = -1;
        }
    }

    return false;
}

/**
 * @brief Perform graph coloring using backtracking.
 *
 * @param graph Adjacency matrix
 * @return A pair containing the minimum number of colors required and the color assignment for nodes
 */

pair<int, vector<int>> graphColoring(vector<vector<int>> &graph)
{
    int N = graph.size();
    vector<int> color(N, -1); 

    if (!graphColoringUtil(graph, color, 0))
    {
        return make_pair(-1, vector<int>());
    }

    int maxColor = 0;
    for (int i = 0; i < N; ++i)
    {
        maxColor = max(maxColor, color[i]);
    }

    return make_pair(maxColor + 1, color); 
}

int main()
{
    int N;

    cout << "Ingresa el número de nodos: ";
    cin >> N;

    vector<vector<int>> graph(N, vector<int>(N, 0));

    // Enter adjacency matrix
    for (int i = 0; i < N; ++i)
    {
        cout << "Ingresa la adyacencia del nodo " << i << ": ";
        for (int j = 0; j < N; ++j)
        {
            cin >> graph[i][j];
        }
    }

    pair<int, vector<int>> result = graphColoring(graph);

    if (result.first == -1)
    {
        cout << "No es posible asignar color a los nodos" << endl;
    }
    else
    {
        cout << "\nEl número mínimo de colores requeridos es: " << result.first << endl;
        cout << "\nAsignación de colores: " << endl;
        for (int i = 0; i < N; ++i)
        {
            cout << "Vértice " << i << ", Color asignado: " << result.second[i] << endl;
        }
        cout << endl;
    }

    return 0;
}
