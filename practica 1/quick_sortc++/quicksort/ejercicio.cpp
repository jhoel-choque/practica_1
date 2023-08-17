#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

template<typename T>
vector<T> quicksort(vector<T>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    T pivot = arr[arr.size() / 2];
    vector<T> left, middle, right;

    for (const auto& x : arr) {
        if (x < pivot) {
            left.push_back(x);
        }
        else if (x == pivot) {
            middle.push_back(x);
        }
        else {
            right.push_back(x);
        }
    }

    vector<T> sorted_left = quicksort(left);
    vector<T> sorted_right = quicksort(right);

    vector<T> result;
    result.reserve(sorted_left.size() + middle.size() + sorted_right.size());
    result.insert(result.end(), sorted_left.begin(), sorted_left.end());
    result.insert(result.end(), middle.begin(), middle.end());
    result.insert(result.end(), sorted_right.begin(), sorted_right.end());

    return result;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<int> list_random;
    for (int i = 0; i < 50000; i++) {
        list_random.push_back(rand() % 10000 + 1);
    }
    //Imprimir lista desordenada
    /*for (int num : list_random) {
        std::cout << num << " ";
    }*/
    
    // Captura el tiempo de inicio
    auto start_time = std::chrono::high_resolution_clock::now();
    vector<int> sorted_list = quicksort(list_random);

    // Captura el tiempo de finalización
    auto end_time = std::chrono::high_resolution_clock::now();
    // Calcula la duración de la ejecución
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    /*cout << "\nLista ordenada ";
    for (int num : sorted_list) {
        std::cout << num << " ";
    }*/
    std::cout << "\nTiempo de ejecución: " << duration.count() << " microsegundos" << std::endl;
    std::cout << std::endl;

    return 0;
}