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
                // Intercambiar los elementos si están en el orden incorrecto
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
        int r = 100; // Tamaño del vector
        vector<int> arr(r);

        // Crea un generador de números aleatorios usando una semilla adecuada
        random_device rd;
        mt19937 gen(rd());

        // Crea una distribución uniforme de números en un rango
        uniform_int_distribution<int> dis(1, 10000); // Cambia el rango según tus necesidades

        // Genera números aleatorios y agrega al vector
        for (int i = 0; i < r; ++i) {
            arr[i] = dis(gen);
        }
        /*
        // Imprime el vector de números aleatorios
        cout << "Vector original: ";
        for (int num : arr) {
            cout << num << " ";
        }*/
        // Captura el tiempo de inicio
        auto start_time = std::chrono::high_resolution_clock::now();

        bubbleSort(arr);

        // Captura el tiempo de finalización
        auto end_time = std::chrono::high_resolution_clock::now();

        // Calcula la duración de la ejecución
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        /*
        cout << "\nVector ordenado: ";
        for (int num : arr) {
            cout << num << " ";
        }*/
        std::cout << "\nTiempo de ejecución: " << duration.count() << " microsegundos" << std::endl;

    }
    return 0;
}
