#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    string filename;
    int n;

    cout << "Ingrese el nombre del archivo de texto: ";
    cin >> filename;

    cout << "Ingrese el valor de n (un entero múltiplo de 4, 16 <= n <= 64): ";
    cin >> n;

    // Validar que n cumple con los requisitos
    if (n % 4 != 0 || n < 16 || n > 64) {
        cout << "El valor de n no cumple con los requisitos." << endl;
        return 1;
    }

    // Abrir el archivo de texto
    ifstream file(filename);

    if (!file) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    // Leer el contenido del archivo y calcular el hash
    vector<int> a(n, 0); // Inicializar el arreglo a con ceros
    int row = 0;
    char c;

    while (file.get(c)) {
        int col = row % n;
        a[col] += static_cast<int>(c);
        row++;

        // Imprimir la tabla
        if (col == n - 1 || file.peek() == EOF) {
            for (int i = 0; i < n; i++) {
                char letter = static_cast<char>(a[i] % 256);
                cout << letter << " ";
            }
            if (file.peek() != EOF) {
                cout << endl;
            } else {
                cout << "-" << endl;
            }
        }
    }

    // Calcular la cadena de salida en hexadecimal
    stringstream hashStream;
    for (int i = 0; i < n; i++) {
        int hexValue = a[i] % 256;
        hashStream << setw(2) << setfill('0') << uppercase << hex << hexValue;
    }

    string hash = hashStream.str();

    // Mostrar el arreglo a
    cout << "Arreglo a: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    // Mostrar la cadena de salida
    cout << "Cadena de salida: " << hash << endl;

    // Cerrar el archivo
    file.close();

    return 0;
}
