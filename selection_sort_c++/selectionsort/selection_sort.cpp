#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

// Function for Selection sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    for (int i = 0; i < 5; i++)
    {


        int r = 50000; // Tama�o del vector
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

        // Imprime el vector de n�meros aleatorios
        /*
        cout << "Vector aleatorio: ";
        for (int num : arr) {
            cout << num << " ";
        }*/
        cout << endl;

        auto start_time = chrono::high_resolution_clock::now();

        // Call the selectionSort function
        selectionSort(arr);

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        /*
        cout << "\nVector ordenado: ";
        for (int num : arr) {
            cout << num << " ";
        }*/
        cout << endl;

        cout << "\nTiempo de ejecuci�n: " << duration.count() << " microsegundos" << endl;
    }
    return 0;
}
