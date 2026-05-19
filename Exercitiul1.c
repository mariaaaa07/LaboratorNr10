#include <stdio.h>
#include <stdlib.h>

// Funcție pentru a inversa două elemente
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funcție pentru a menține proprietatea de Max-Heap
void heapify(int arr[], int n, int i) {
    int largest = i;       // Inițializăm cel mai mare ca fiind rădăcina
    int left = 2 * i + 1;  // Stânga = 2*i + 1
    int right = 2 * i + 2; // Dreapta = 2*i + 2

    // Dacă fiul stâng este mai mare decât rădăcina
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Dacă fiul drept este mai mare decât cel mai mare de până acum
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Dacă cel mai mare nu este rădăcina
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursiv transformăm subarborele afectat într-un heap
        heapify(arr, n, largest);
    }
}

// Funcția principală de Heap Sort
void heapSort(int arr[], int n) {
    // Construim structura de Heap (rearanjăm vectorul)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extragem pe rând elemente din heap
    for (int i = n - 1; i > 0; i--) {
        // Mutăm rădăcina curentă la sfârșit
        swap(&arr[0], &arr[i]);

        // Apelăm heapify pe heap-ul redus
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Vectorul inițial: \n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Vectorul sortat prin Heap Sort: \n");
    printArray(arr, n);
    return 0;
}