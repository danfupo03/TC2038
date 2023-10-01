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
 * 
 * @complexity O(m*(n-m))
 */
void search(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();

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
            cout << "(true) " << i << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "(false) Cadena no encontrada en la transmision" << endl;
    }
}

/**
 * @brief Function that generates a palindrome from a string.
 *
 * @param maliciusString
 * @return the palindrome generated.
 * 
 * @complexity O(n)
 */
string generatePalindrome(string maliciusString)
{
    string palindrome = "";
    int size = maliciusString.length();
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
 * 
 * @complexity O(m*(n-m))
 */
vector<pair<int, int>> searchPalindrome(string maliciusString, string transmission)
{
    string mCodePalindrome = generatePalindrome(maliciusString);

    vector<pair<int, int>> positions;

    int lenTransmission = transmission.length();

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

/**
 * @brief Function that recieves two strings and returns the longest common substring.
 *
 * @param s1
 * @param s2
 * @return the longest common substring.
 * 
 * @complexity O(n*m)
 */
string longuestCommonSubstring(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();
    int dp[n + 1][m + 1];
    int mx = 0, end = -1;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; ++j)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                if (mx < dp[i][j])
                {
                    mx = dp[i][j];
                    end = i - 1;
                }
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }

    return s1.substr(end - mx + 1, mx);
}

int main(int argc, char *argv[])
{
    ifstream inputFileT1, inputFileT2, inputFileMC1, inputFileMC2, inputFileMC3;
    string line, transmision1, transmision2, mcode1, mcode2, mcode3;

    if (argc < 6)
    {
        cout << "Uso: " << argv[0] << " <transmision1.txt> <transmision2.txt> <mcode1.txt> <mcode2.txt> <mcode3.txt>" << endl;
        return 1;
    }

    // Opening files
    inputFileT1.open(argv[1]);
    inputFileT2.open(argv[2]);
    inputFileMC1.open(argv[3]);
    inputFileMC2.open(argv[4]);
    inputFileMC3.open(argv[5]);

    if (!inputFileT1 || !inputFileT2 || !inputFileMC1 || !inputFileMC2 || !inputFileMC3)
    {
        cout << "Error abriendo los archivos" << endl;
        return 1;
    }

    // Reading Transmissions
    while (getline(inputFileT1, line))
    {
        transmision1 += line;
    }

    while (getline(inputFileT2, line))
    {
        transmision2 += line;
    }

    // Reading Malicious Codes
    inputFileMC1 >> mcode1;
    inputFileMC2 >> mcode2;
    inputFileMC3 >> mcode3;

    cout << "Transmision 1: " << transmision1 << endl
         << endl;
    cout << "Transmision 2: " << transmision2 << endl
         << endl;
    cout << "mcode 1: " << mcode1 << endl
         << endl;
    cout << "mcode 2: " << mcode2 << endl
         << endl;
    cout << "mcode 3: " << mcode3 << endl
         << endl;

    cout << "La cadena maliciosa1 se encuentra en la transmision1: " << endl;
    search(mcode1, transmision1);

    cout << "\nLa cadena maliciosa2 se encuentra en la transmision1: " << endl;
    search(mcode2, transmision1);

    cout << "\nLa cadena maliciosa3 se encuentra en la transmision1: " << endl;
    search(mcode3, transmision1);

    cout << "\nLa cadena maliciosa1 se encuentra en la transmision2: " << endl;
    search(mcode1, transmision2);

    cout << "\nLa cadena maliciosa2 se encuentra en la transmision2: " << endl;
    search(mcode2, transmision2);

    cout << "\nLa cadena maliciosa3 se encuentra en la transmision2: " << endl;
    search(mcode3, transmision2);

    cout << "\nPosiciones de los Palindromos maliciosos: " << endl;

    cout << "\nPalindromo de cadena maliciosa1 en la transmicion 1: " << endl;
    vector<pair<int, int>> positions = searchPalindrome(mcode1, transmision1);
    for (int i = 0; i < positions.size(); i++)
    {
        cout << "Posicion inicial: " << positions[i].first << " Posicion final: " << positions[i].second << endl;
    }

    cout << "\nPalindromo de cadena maliciosa2 en la transmicion 1: " << endl;
    positions = searchPalindrome(mcode2, transmision1);
    for (int i = 0; i < positions.size(); i++)
    {
        cout << "Posicion inicial: " << positions[i].first << " Posicion final: " << positions[i].second << endl;
    }

    cout << "\nPalindromo de cadena maliciosa3 en la transmicion 1: " << endl;
    positions = searchPalindrome(mcode3, transmision1);
    for (int i = 0; i < positions.size(); i++)
    {
        cout << "Posicion inicial: " << positions[i].first << " Posicion final: " << positions[i].second << endl;
    }

    cout << "\nPalindromo de cadena maliciosa1 en la transmicion 2: " << endl;
    positions = searchPalindrome(mcode1, transmision2);
    for (int i = 0; i < positions.size(); i++)
    {
        cout << "Posicion inicial: " << positions[i].first << " Posicion final: " << positions[i].second << endl;
    }

    cout << "\nPalindromo de cadena maliciosa2 en la transmicion 2: " << endl;
    positions = searchPalindrome(mcode2, transmision2);
    for (int i = 0; i < positions.size(); i++)
    {
        cout << "Posicion inicial: " << positions[i].first << " Posicion final: " << positions[i].second << endl;
    }

    cout << "\nPalindromo de cadena maliciosa3 en la transmicion 2: " << endl;
    positions = searchPalindrome(mcode3, transmision2);
    for (int i = 0; i < positions.size(); i++)
    {
        cout << "Posicion inicial: " << positions[i].first << " Posicion final: " << positions[i].second << endl;
    }

    cout << "\nSubcadena comun mas larga entre la transmision 1 y la transmision 2: " << endl;
    string longestCommonSubstring = longuestCommonSubstring(transmision1, transmision2);
    cout << longestCommonSubstring << endl;

    return 0;
}
