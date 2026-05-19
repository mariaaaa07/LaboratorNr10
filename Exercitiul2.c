#include <stdio.h>

// Funcție utilitară pentru a găsi maximul dintre două numere
int max(int a, int b) { 
    return (a > b) ? a : b; 
}

// Returnează valoarea maximă ce poate fi pusă într-un rucsac de capacitate W
int rucsac(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    // Construim tabela K[][] de jos în sus
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    
    printf("Valoarea maximă ce poate fi transportată: %d\n", rucsac(W, wt, val, n));
    return 0;
}