#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <limits.h>
// #include <utility>

using namespace std;

// overload << for a int int map
ostream &operator<<(ostream &os, const map<int, int> &m)
{
    for (auto i : m)
    {
        os << i.first << " " << i.second << endl;
    }
    return os;
}

map<int, int> coinsGreedy(const vector<int> &denominacionesG, const int costo, const int pago)
{
    // copy the vector and sort it in descending order
    vector<int> denominaciones(denominacionesG);
    sort(denominaciones.begin(), denominaciones.end(), greater<int>());

    map<int, int> cambios;
    int total = pago - costo;
    int i = 0;
    while (total > 0)
    {
        if (i >= denominaciones.size())
        {
            cout << "No hay Sistema Joven" << endl;
            return {{-1, -1}};
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

map<int, int> obtenerMejorCambio(const vector<int> &denominacionesG, int costo, int pago)
{
    vector<int> denominaciones(denominacionesG);
    sort(denominaciones.begin(), denominaciones.end(), less<int>());

    map<int, int> cambios;

    int total = pago - costo;

    const int numDenominaciones = denominaciones.size();

    vector<vector<int>> dp(numDenominaciones, vector<int>(total + 1, 0));

    dp[0][0] = 0;

    for (int currDenom = 0; currDenom < numDenominaciones; currDenom++)
    {
        for (int currCambio = 1; currCambio <= total; currCambio++)
        {
            int top;
            if (currDenom == 0)
            {
                top = INT32_MAX;
            }
            else
            {
                top = dp[currDenom - 1][currCambio];
            }
            if (denominaciones[currDenom] <= currCambio)
            {

                int prev = dp[currDenom][currCambio - denominaciones[currDenom]];
                dp[currDenom][currCambio] = min(top, prev + 1);
            }
            else
            {
                dp[currDenom][currCambio] = top;
            }
        }
    }

    if (dp.back().back() == INT32_MAX)
    {
        cout << "No hay Sistema Joven1" << endl;
        return {{-1, -1}};
    }

    int currDenom = numDenominaciones - 1;
    int currCambio = total;

    while (currCambio > 0 && currDenom > 0)
    {
        if (dp[currDenom][currCambio] == dp[currDenom - 1][currCambio])
        {
            currDenom--;
        }
        else
        {
            cambios[denominaciones[currDenom]]++;
            currCambio -= denominaciones[currDenom];
        }
    }

    if (currDenom == 0)
    {
        cambios[denominaciones[currDenom]] += currCambio / denominaciones[currDenom];
    }

    return cambios;
}

int main()
{
    int numDenominaciones, costo, pago;
    cout << "Ingrese el numero de denominaciones: ";
    cin >> numDenominaciones;
    vector<int> denominaciones(numDenominaciones);
    for (int i = 0; i < numDenominaciones; i++)
    {
        cout << "Ingrese la denominacion " << i + 1 << ": ";
        cin >> denominaciones[i];
    }
    cout << "Ingrese el costo: ";
    cin >> costo;
    cout << "Ingrese el pago: ";
    cin >> pago;

    // Greedy
    cout << "Greedy: " << endl;

    map<int, int> resGreedy = coinsGreedy(denominaciones, costo, pago);

    cout << "Denominacion \tCantidad" << endl;
    for (const auto &par : resGreedy)
        cout << par.first << "\t\t" << par.second << endl;

    // DP
    cout << endl
         << "DP: " << endl;

    map<int, int> res = obtenerMejorCambio(denominaciones, costo, pago);

    cout << "Denominacion \tCantidad" << endl;
    for (const auto &par : res)
        cout << par.first << "\t\t" << par.second << endl;

    return 0;
}