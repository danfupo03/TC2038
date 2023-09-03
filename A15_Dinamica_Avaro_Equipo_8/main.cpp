#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
// #include <utility>

using std::cout;
using std::endl;
using std::greater;
using std::map;
using std::pair;
using std::sort;
using std::vector;

/**
 * @brief ostream operator for map<int, int>
 *
 * @param os
 * @param m
 * @return ** std::ostream&
 *
 * @complexity O(n)
 */
std::ostream &operator<<(std::ostream &os, const map<int, int> &m)
{
    for (auto i : m)
    {
        os << i.first << " " << i.second << endl;
    }
    return os;
}

/**
 * @brief Greedy algorithm for coin change problem
 *
 * @param denominaciones
 * @param costo
 * @param pago
 * @return map<int, int>
 *
 * @complexity O(n)
 */
map<int, int> coinsGreedy(vector<int> denominaciones, int costo, int pago)
{
    sort(denominaciones.begin(), denominaciones.end(), greater<int>());
    map<int, int> cambios;
    int total = pago - costo;
    int i = 0;
    while (total > 0)
    {
        if (i >= denominaciones.size())
        {
            cout << "No hay Sistema Joven" << endl;
            return cambios;
        }
        if (total >= denominaciones[i])
        {
            total -= denominaciones[i];
            cambios[denominaciones[i]]++;
        }
        else
        {
            i++;
        }
    }
    return cambios;
}

/**
 * @brief DFS algorithm for coin change problem
 *
 * @param i
 * @param cambio
 * @param denominaciones
 * @return map<int, int>
 *
 * @complexity O(n)
 */
map<int, int> dfs(int i, int cambio, vector<int> denominaciones)
{
    if (cambio == 0)
    {
        return {{i, 1}};
    }
    if (cambio <= 0)
    {
        return {};
    }
    else if (i >= denominaciones.size())
    {
        return {};
    }

    auto res1 = dfs(i + 1, cambio, denominaciones);
    auto res2 = dfs(i, cambio - denominaciones[i], denominaciones);

    cout << "i: " << i << " cambio: " << cambio << endl;
    cout << "Res1: " << res1 << endl;
    cout << "Res2: " << res2 << endl;

    int val1 = 0;
    for (auto i : res1)
    {
        val1 += i.second;
    }

    int val2 = 0;
    for (auto i : res2)
    {
        val2 += i.second;
    }

    if (val1 < val2)
    {
        return res1;
    }
    else
    {
        return res2;
    }
}

/**
 * @brief Dynamic Programming algorithm for coin change problem
 *
 * @param denominaciones
 * @param costo
 * @param pago
 * @return map<int, int>
 *
 * @complexity O(n)
 */
map<int, int> coinsDP(vector<int> denominaciones, int costo, int pago)
{
    return dfs(0, pago - costo, denominaciones);
}

/**
 * @brief Dynamic Programming algorithm for coin change problem
 *
 * @param denominaciones
 * @param costo
 * @param pago
 * @return map<int, int>
 *
 * @complexity O(n)
 */
std::map<int, int> obtenerMejorCambio(const std::vector<int> &denominaciones, int costo, int pago)
{
    std::map<int, int> cambios;

    int total = pago - costo;

    const int numDenominaciones = denominaciones.size();

    std::vector<std::vector<int>> dp(total + 1, std::vector<int>(numDenominaciones, -1));
    std::vector<int> seleccion(total + 1, -1);

    dp[0][0] = 0;

    for (int i = 0; i <= total; i++)
    {
        for (int j = 0; j < numDenominaciones; j++)
        {
            if (denominaciones[j] <= i)
            {
                if (dp[i - denominaciones[j]][j] != -1)
                {
                    dp[i][j] = dp[i - denominaciones[j]][j] + 1;
                    seleccion[i] = j;
                }
            }

            if (j > 0 && dp[i][j - 1] != -1 && (dp[i][j] == -1 || dp[i][j - 1] < dp[i][j]))
            {
                dp[i][j] = dp[i][j - 1];
                seleccion[i] = j - 1;
            }
        }
    }

    if (dp[total][numDenominaciones - 1] == -1)
    {
        // No se encontró una solución
        return cambios;
    }

    int j = numDenominaciones - 1;
    int i = total;

    while (i > 0 && j >= 0)
    {
        if (seleccion[i] == j)
        {
            cambios[denominaciones[j]]++;
            i -= denominaciones[j];
        }
        else
        {
            j--;
        }
    }

    // Agregar las denominaciones que no se usaron con cantidad 0
    for (const int denominacion : denominaciones)
    {
        if (cambios.find(denominacion) == cambios.end())
        {
            cambios[denominacion] = 0;
        }
    }

    return cambios;
}

int main()
{
    // std::vector<int> denominaciones = {5, 10, 20, 25};
    // int costo = 160;
    // int pago = 200;

    std::vector<int> denominaciones = {1, 10, 7};
    int costo = 85;
    int pago = 100;

    // Greedy

    std::cout << "Greedy" << endl;

    std::map<int, int> resGreedy = coinsGreedy(denominaciones, costo, pago);

    for (const auto &par : resGreedy)
    {
        std::cout << par.first << " " << par.second << std::endl;
    }

    // DP

    std::cout << "DP" << endl;

    std::map<int, int> res = obtenerMejorCambio(denominaciones, costo, pago);

    for (const auto &par : res)
    {
        std::cout << par.first << " " << par.second << std::endl;
    }

    return 0;
}