#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
    string filename;
    int n;

    cout << "\nIngrese el nombre del archivo de texto: ";
    cin >> filename;

    cout << "Ingrese el valor de n (un entero múltiplo de 4, 16 <= n <= 64): ";
    cin >> n;
    cout << endl;

    // Validar que n cumple con los requisitos
    if (n % 4 != 0 || n < 16 || n > 64)
    {
        cout << "El valor de n no cumple con los requisitos." << endl;
        return 1;
    }

    // Abrir el archivo de texto
    ifstream file(filename);

    if (!file)
    {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    // Leer el contenido del archivo y calcular el hash
    vector<int> result(n, 0); // Inicializar el arreglo a con ceros
    int i = 0;
    int row = 0;
    int col = 0;
    char c;

    while (file.get(c))
    {
        col = i % n;
        result[col] += (int)(c);
        if (c == '\n')
            c = '-';

        cout << c << " ";
        if (col == n - 1)
        {
            cout << endl;
        }
        i++;
    }

    int remaining = n - (i % n);

    for (int j = 0; j < remaining; j++)
    {
        col = i % n;
        result[col] += n;
        cout << "[ ";
        if (col == n - 1)
        {
            cout << endl;
        }
        i++;
    }

    // Mostrar el arreglo a
    cout << "\nArreglo:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << result[i] % 256 << " ";
    }
    cout << endl;

    // Calcular la cadena de salida en hexadecimal
    stringstream hashStream;
    for (int i = 0; i < n; i += 2)
    {
        int hexValue = result[i] % 256;
        int hexValue2 = result[i + 1] % 256;
        hashStream << uppercase << hex << hexValue << hexValue2 << " ";
    }

    string hash = hashStream.str();

    // Mostrar la cadena de salida
    cout << "\nCadena de salida: " << "\n" << hash << endl;

    // Cerrar el archivo
    file.close();

    return 0;
}
