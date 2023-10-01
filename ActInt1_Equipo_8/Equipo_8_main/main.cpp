#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

/**
 * @brief Function that searches for a string in a transmission.
 *
 * @param pat
 * @param txt
 */
void search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    if (M > N)
    {
        cout << "La longitud del patron es mayor que la de la cadena." << endl;
        return;
    }

    bool found = false;

    for (int i = 0; i <= N - M; i++)
    {
        int j;

        for (j = 0; j < M; j++)
        {
            if (txt[i + j] != pat[j])
                break;
        }
        if (j == M)
        {
            cout << "\n(true) " << i << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "\n(false) Cadena no encontrada en la transmision" << endl;
    }
}

/**
 * @brief Function that generates a palindrome from a string.
 *
 * @param maliciusString
 * @return the palindrome generated.
 */

string generatePalindrome(char *maliciusString)
{
    string palindrome = "";
    int size = strlen(maliciusString);
    for (int i = size - 1; i >= 0; i--)
    {
        palindrome += maliciusString[i];
    }
    return palindrome;
}

/**
 * @brief Function that recieves a malicius string and search for a palindrome.
 * in the string.
 *
 * @param maliciusString
 * @return the initial position and final positions of the palindrome in the string.
 */
vector<pair<int, int>> searchPalindrome(char *maliciusString, char *transmission)
{
    string mCodePalindrome = generatePalindrome(maliciusString);

    vector<pair<int, int>> positions;

    int lenTransmission = strlen(transmission);

    for (int i = 0; i < lenTransmission; i++)
    {
        int j = 0;
        int k = i;
        while (transmission[k] == mCodePalindrome[j] && j < mCodePalindrome.length())
        {
            j++;
            k++;
        }
        if (j == mCodePalindrome.length())
        {
            positions.push_back(make_pair(i, k - 1));
        }
    }

    return positions;
}

int main(int argc, char *argv[])
{
    ifstream inputFile1, inputFile2;
    char s1[1000];
    char s2[1000] = "";
    char line[1000];

    if (argc < 3)
    {
        cout << "Uso: " << argv[0] << " <input_file> <input_file2>" << endl;
        return 1;
    }

    inputFile1.open(argv[1]);
    inputFile2.open(argv[2]);

    if (!inputFile1 || !inputFile2)
    {
        cout << "Error abriendo el archivo" << endl;
        return 1;
    }

    inputFile1 >> s1;

    while (inputFile2.getline(line, sizeof(line)))
    {
        strcat(s2, line);
    }

    cout << "La cadena maliciosa: " << s1 << " se encuentra en la transmision: " << endl;

    search(s1, s2);

    vector<pair<int, int>> positions = searchPalindrome(s1, s2);

    cout << "\nPosiciones de los palindromos maliciosos: " << endl;

    for (int i = 0; i < positions.size(); i++)
    {
        cout << "Posicion inicial: " << positions[i].first << " Posicion final: " << positions[i].second << endl;
    }

    return 0;
}
