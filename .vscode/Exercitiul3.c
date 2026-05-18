#include <stdio.h>
#include <stdbool.h>

#define NODURI 5
#define INF 999999

// Structură pentru noduri în A*
typedef struct {
    int id;
    int g; // Costul de la pornire la nodul curent
    int h; // Euristica (distanța estimată până la țintă)
    int f; // f = g + h
    int parinte;
} Nod;

void aStar(int graf[NODURI][NODURI], int euristica[NODURI], int start, int tinta) {
    bool openSet[NODURI] = {false};
    bool closedSet[NODURI] = {false};
    Nod noduri[NODURI];

    for (int i = 0; i < NODURI; i++) {
        noduri[i].id = i;
        noduri[i].g = INF;
        noduri[i].f = INF;
        noduri[i].parinte = -1;
    }

    noduri[start].g = 0;
    noduri[start].h = euristica[start];
    noduri[start].f = euristica[start];
    openSet[start] = true;

    while (true) {
        // Găsim nodul din openSet cu cel mai mic f
        int curent = -1;
        int minF = INF;
        for (int i = 0; i < NODURI; i++) {
            if (openSet[i] && noduri[i].f < minF) {
                minF = noduri[i].f;
                curent = i;
            }
        }

        // Dacă nu mai sunt noduri de explorat sau am ajuns la destinație
        if (curent == -1) {
            printf("Nu s-a găsit niciun drum.\n");
            return;
        }
        if (curent == tinta) {
            printf("Drumul optim a fost găsit! Cost total: %d\nTraseu: ", noduri[tinta].g);
            int p = tinta;
            int drum[NODURI], idx = 0;
            while (p != -1) {
                drum[idx++] = p;
                p = noduri[p].parinte;
            }
            for (int i = idx - 1; i >= 0; i--) {
                printf("%d ", drum[i]);
            }
            printf("\n");
            return;
        }

        openSet[curent] = false;
        closedSet[curent] = true;

        // Verificăm vecinii nodului curent
        for (int vecin = 0; vecin < NODURI; vecin++) {
            if (graf[curent][vecin] != 0 && !closedSet[vecin]) {
                int g_tentativ = noduri[curent].g + graf[curent][vecin];

                if (!openSet[vecin]) {
                    openSet[vecin] = true;
                } else if (g_tentativ >= noduri[vecin].g) {
                    continue; // Nu este un drum mai bun
                }

                noduri[vecin].parinte = curent;
                noduri[vecin].g = g_tentativ;
                noduri[vecin].h = euristica[vecin];
                noduri[vecin].f = noduri[vecin].g + noduri[vecin].h;
            }
        }
    }
}

int main() {
    // Matricea de adiacență a grafului (0 înseamnă că nu există legătură directă)
    int graf[NODURI][NODURI] = {
        {0, 4, 3, 0, 0},
        {4, 0, 1, 2, 0},
        {3, 1, 0, 4, 2},
        {0, 2, 4, 0, 5},
        {0, 0, 2, 5, 0}
    };
    
    // Valorile euristice estimate pentru fiecare nod până la ținta (Nodul 4)
    int euristica[NODURI] = {7, 4, 2, 3, 0};

    aStar(graf, euristica, 0, 4);
    return 0;
}