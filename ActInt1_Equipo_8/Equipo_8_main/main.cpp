#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
 * @brief Función que busca una cadena en otra.
 * 
 * @param pat 
 * @param txt 
 */
void search(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    if (M > N)
    {
        cout << "La longitud del patrón es mayor que la de la cadena." << endl;
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
        cout << "(false) Cadena no encontrada en la transmisión" << endl;
    }
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

    search(s1, s2);

    return 0;
}
