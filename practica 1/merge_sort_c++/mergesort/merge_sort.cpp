#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>   // Incluye la biblioteca random
#include <chrono>   // Incluye la biblioteca chrono

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> left_half(n1);
    std::vector<int> right_half(n2);

    for (int i = 0; i < n1; ++i)
        left_half[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        right_half[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (left_half[i] <= right_half[j]) {
            arr[k] = left_half[i];
            ++i;
        }
        else {
            arr[k] = right_half[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = left_half[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = right_half[j];
        ++j;
        ++k;
    }
}

void merge_sort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    for (int i = 0; i < 5; i++)
    {
        //repetir el codigo 5 veces

        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        int n = 50000; // Tamaño de la lista
        std::vector<int> unsorted_list;


        // Crea un generador de números aleatorios usando una semilla adecuada
        std::random_device rd;
        std::mt19937 gen(rd());

        // Crea una distribución uniforme de números en un rango
        std::uniform_int_distribution<int> dis(1, 10000); // Cambia el rango según tus necesidades

        // Genera números aleatorios y agrega a la lista
        for (int i = 0; i < n; ++i) {
            unsorted_list.push_back(dis(gen));
        }


        // Imprime la lista generada
        /*
        std::cout << "Lista aleatoria: ";
        for (int num : unsorted_list) {
            std::cout << num << " ";
        }*/

        // Captura el tiempo de inicio
        auto start_time = std::chrono::high_resolution_clock::now();

        merge_sort(unsorted_list, 0, unsorted_list.size() - 1);

        // Captura el tiempo de finalización
        auto end_time = std::chrono::high_resolution_clock::now();

        // Calcula la duración de la ejecución
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        // Imprime la lista ordenada
        /*
        std::cout << "\nLista ordenada:";
        for (int num : unsorted_list) {
            std::cout << " " << num;
        }*/
        std::cout << "\nTiempo de ejecución: " << duration.count() << " microsegundos" << std::endl;
    }
    std::cout << std::endl;

    return 0;
}