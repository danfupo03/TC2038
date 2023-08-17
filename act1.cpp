#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

using namespace std;

const double PI = 3.14159265358979323846;

/**
 * @brief Calcula el volumen de un cilindro
 *
 * @param radius Radio en cm
 * @param height Altura en cm
 * @return int
 */
float volumeOfCilinder(float radius, float height)
{
    return PI * radius * radius * height;
}

/**
 * @brief Calcula el número de refrescos que puede producit una máquina
 *
 * @param volume  Volumen del cilindro en cm3
 * @param mililiters Volumen del refresco en ml
 * @return int
 */
int numberOfBottles(float volume, float mililiters)
{
    return (int)floor(volume / mililiters);
}

/**
 * @brief Calcula el número de días que se necesitan para producir una cantidad de camisas
 *
 * @param shirts Cantidad de camisas
 */
void daysToProduceShirts(int shirts)
{
    int days = 0;
    srand(time(NULL));

    float producedShirts = 0;
    float currProducedShirts;

    while (producedShirts < shirts)
    {
        float line1 = rand() % 1000 / 10;
        float line2 = rand() % 1000 / 10;

        days++;

        currProducedShirts = line1 + line2;
        
        producedShirts += currProducedShirts;
        cout << "Dia " << days << ": " << endl;
        cout << "Produccion en linea 1: " << line1 << endl;
        cout << "Produccion en linea 2: " << line2 << endl;
        cout << "El dia " << days << " se produjeron " << currProducedShirts << " camisas. Total: " << producedShirts << endl;
        cout << "-----------------------------" << endl;
    }
    cout << "Se necesitaron " << days << " dia(s) para producir " << shirts << " camisas." << endl;
}

int main()
{
    float radius, height, mililiters;
    cout << "Ingrese el radio del contenedor (metros): ";
    cin >> radius;
    cout << "Ingrese la altura del contenedor (metros): ";
    cin >> height;
    cout << "Ingrese el volumen (ml) del refesco: ";
    cin >> mililiters;
    float volume = volumeOfCilinder(radius * 100, height * 100);
    cout << "El volumen del contenedor es: " << volume << " cm3" << endl;
    cout << "El numero de refrescos que se pueden llenar con una carga son: " << numberOfBottles(volume, mililiters) << endl;

    cout << "-----------------------------" << endl;

    int shirts;
    cout << "Ingrese el numero de camisas: ";
    cin >> shirts;
    daysToProduceShirts(shirts);

    return 0;
}