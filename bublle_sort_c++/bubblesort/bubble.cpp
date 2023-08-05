#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Intercambiar los elementos si est�n en el orden incorrecto
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    for (int i = 0; i < 5; i++)
    {
        int r = 100; // Tama�o del vector
        vector<int> arr(r);

        // Crea un generador de n�meros aleatorios usando una semilla adecuada
        random_device rd;
        mt19937 gen(rd());

        // Crea una distribuci�n uniforme de n�meros en un rango
        uniform_int_distribution<int> dis(1, 10000); // Cambia el rango seg�n tus necesidades

        // Genera n�meros aleatorios y agrega al vector
        for (int i = 0; i < r; ++i) {
            arr[i] = dis(gen);
        }
        /*
        // Imprime el vector de n�meros aleatorios
        cout << "Vector original: ";
        for (int num : arr) {
            cout << num << " ";
        }*/
        // Captura el tiempo de inicio
        auto start_time = std::chrono::high_resolution_clock::now();

        bubbleSort(arr);

        // Captura el tiempo de finalizaci�n
        auto end_time = std::chrono::high_resolution_clock::now();

        // Calcula la duraci�n de la ejecuci�n
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        /*
        cout << "\nVector ordenado: ";
        for (int num : arr) {
            cout << num << " ";
        }*/
        std::cout << "\nTiempo de ejecuci�n: " << duration.count() << " microsegundos" << std::endl;

    }
    return 0;
}
