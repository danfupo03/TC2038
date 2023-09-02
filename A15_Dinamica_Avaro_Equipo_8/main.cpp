
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

map<int, int> coinsDP(vector<int> denominaciones, int costo, int pago)
{
    return dfs(0, pago - costo, denominaciones);
}

int main(int argc, char const *argv[])
{
    vector<int> denominaciones = {1, 2, 5, 10, 20, 50};
    int costo = 0;
    int pago = 521;
    auto res = coinsGreedy(denominaciones, costo, pago);
    cout << "Greedy:" << endl;
    for (auto i : res)
    {
        cout << i.first << " " << i.second << endl;
    }
    cout << endl;
    cout << "DP:" << endl;
    res = coinsDP(denominaciones, costo, pago);
    for (auto i : res)
    {
        cout << i.first << " " << i.second << endl;
    }
    cout << endl;

    return 0;
}