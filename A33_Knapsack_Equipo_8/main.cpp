#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Función que calcula la ganancia óptima de la mochila
 * 
 * @param N 
 * @param values 
 * @param weights 
 * @param W 
 * @param matrix 
 * @return int 
 * 
 * @complejidad O(NW)
 */
int knapsack(int N, vector<int> &values, vector<int> &weights, int W, vector<vector<int>> &matrix)
{
    for (int i = 0; i <= N; ++i)
    {
        for (int j = 0; j <= W; ++j)
        {
            if (i == 0 || j == 0)
            {
                matrix[i][j] = 0;
            }
            else if (weights[i - 1] <= j)
            {
                matrix[i][j] = max(values[i - 1] + matrix[i - 1][j - weights[i - 1]], matrix[i - 1][j]);
            }
            else
            {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }
    return matrix[N][W];
}

int main()
{
    int N, W;

    cout << "Ingrese el número de elementos: ";
    cin >> N;

    vector<int> values(N);
    vector<int> weights(N);
    for (int i = 0; i < N; ++i)
    {
        cout << "Ingrese el valor del elemento " << i + 1 << ": ";
        cin >> values[i];
    }
    for (int i = 0; i < N; ++i)
    {
        cout << "Ingrese el peso del elemento " << i + 1 << ": ";
        cin >> weights[i];
    }

    cout << "Ingrese la capacidad de la mochila: ";
    cin >> W;

    vector<vector<int>> matrix(N + 1, vector<int>(W + 1, 0));
    int profit = knapsack(N, values, weights, W, matrix);

    cout << "\nBeneficio óptimo: " << profit << endl;

    cout << "\nMatriz generada:" << endl;
    for (int i = 0; i <= N; ++i)
    {
        for (int w = 0; w <= W; ++w)
        {
            cout << matrix[i][w] << " ";
        }
        cout << endl;
    }

    return 0;
}
