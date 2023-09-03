
// func that return a pair od ints

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

// overload << for a int int map
std::ostream &operator<<(std::ostream &os, const map<int, int> &m)
{
    for (auto i : m)
    {
        os << i.first << " " << i.second << endl;
    }
    return os;
}

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

map<int, int> dfs(int i, int cambio, vector<int> denominaciones, map<pair<int, int>, map<int, int>> memo = {})
{
    if (memo.find({i, cambio}) != memo.end())
    {
        return memo[{i, cambio}];
    }

    if (cambio == 0)
    {
        return {{0, 0}};
    }
    if (cambio < 0 || i >= denominaciones.size())
    {
        return {};
    }
    int minCoins = 1e9;
    map<int, int> minDenominaciones;
    map<int, int> res;
    if (cambio >= denominaciones[i])
    {
        res = dfs(i, cambio - denominaciones[i], denominaciones);
        if (!res.empty())
        {
            res[denominaciones[i]]++;
            int numCoins = 1;
            for (auto i : res)
                numCoins += i.second;

            if (numCoins < minCoins)
            {
                minCoins = numCoins;
                minDenominaciones = res;
            }
        }
    }

    res = dfs(i + 1, cambio, denominaciones);
    if (!res.empty())
    {
        int numCoins = 0;
        for (auto i : res)
            numCoins += i.second;

        if (numCoins < minCoins)
        {
            minCoins = numCoins;
            minDenominaciones = res;
        }
    }

    memo[{i, cambio}] = minDenominaciones;
    return minDenominaciones;
}

map<int, int> coinsDP(vector<int> denominaciones, int costo, int pago)
{
    return dfs(0, pago - costo, denominaciones);
}

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

    vector<int> denominaciones = {1, 2, 5, 10, 20, 50};
    int costo = 0;
    int pago = 521;

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