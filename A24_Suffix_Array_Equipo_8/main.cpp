#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

/**
 * @brief Compara dos pares (posición, substring) de manera insensible a mayúsculas/minúsculas.
 *
 * Esta función compara dos pares (posición, substring) de manera insensible a mayúsculas/minúsculas.
 *
 * @param a Primer par a comparar.
 * @param b Segundo par a comparar.
 * @return Devuelve true si a es menor que b en orden alfabético insensible a mayúsculas/minúsculas, false en caso contrario.
 * 
 * @complexity O(n), donde 'n' es la longitud de la cadena.
 */
bool compareSubstrings(const pair<int, string>& a, const pair<int, string>& b) {
    string aLower = a.second;
    string bLower = b.second;

    transform(aLower.begin(), aLower.end(), aLower.begin(), ::tolower);
    transform(bLower.begin(), bLower.end(), bLower.begin(), ::tolower);

    return aLower < bLower;
}

/**
 * @brief Genera y ordena los substrings de una cadena dada.
 *
 * Esta función recibe una cadena de entrada, genera todos los substrings posibles y los ordena alfabéticamente.
 * Luego, muestra los substrings ordenados junto con su posición inicial.
 *
 * @param input La cadena de entrada.
 *
 * @details El tiempo de ejecución de esta función depende de la longitud de la cadena de entrada.
 *          - Generar los substrings lleva tiempo lineal en función de la longitud de la cadena, O(n^2), donde 'n' es la longitud de la cadena.
 *          - Ordenar el vector de substrings toma O(n*log(n)).
 *          - Mostrar los substrings toma tiempo lineal en función del número de substrings, que es O(n^2) en el peor caso.
 *          Por lo tanto, la complejidad total es dominada por la ordenación y es O(n*log(n)), donde 'n' es la longitud de la cadena.
 * 
 * @complexity O(n*log(n)), donde 'n' es la longitud de la cadena.
 */
void generateAndSortSubstrings(const string& input) {
    vector<pair<int, string>> substrings;

    // Generar substrings y guardar los únicos en el vector
    for (int i = 0; i < input.length(); i++) {
        string substr = input.substr(i, input.length());
        substrings.push_back(make_pair(i, substr));
    }

    // Ordenar el vector alfabéticamente
    sort(substrings.begin(), substrings.end(), compareSubstrings);

    // Mostrar los substrings
    for (int i = 0; i < substrings.size(); i++) {
        cout << substrings[i].first << " " << substrings[i].second << endl;
    }
}

int main() {
    string input;

    cout << "\nIngresa una cadena: ";
    cin >> input;

    generateAndSortSubstrings(input);

    cout << endl;

    return 0;
}
