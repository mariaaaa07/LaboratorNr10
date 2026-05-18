#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Structură pentru un nod din lista înlănțuită (pentru coliziuni)
typedef struct Node {
    char cheie[50];
    char valoare[100];
    struct Node* next;
} Node;

// Structura pentru Hash Table
typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

// Funcția Hash elementară (Suma valorilor ASCII % TABLE_SIZE)
int hashFunction(char* str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }
    return sum % TABLE_SIZE;
}

// Inițializare tabelă
void initTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
}

// 1. ADĂUGARE (Inserare)
void inserare(HashTable* ht, char* cheie, char* valoare) {
    int index = hashFunction(cheie);
    
    // Verificăm dacă cheia există deja pentru a-i face update la definiție
    Node* curr = ht->buckets[index];
    while (curr != NULL) {
        if (strcmp(curr->cheie, cheie) == 0) {
            strcpy(curr->valoare, valoare);
            return;
        }
        curr = curr->next;
    }
    
    // Alocăm un nod nou dacă cheia nu există
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->cheie, cheie);
    strcpy(newNode->valoare, valoare);
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
    printf("Cuvântul '%s' a fost adăugat cu succes.\n", cheie);
}

// 2. CĂUTARE
char* cautare(HashTable* ht, char* cheie) {
    int index = hashFunction(cheie);
    Node* curr = ht->buckets[index];
    
    while (curr != NULL) {
        if (strcmp(curr->cheie, cheie) == 0) {
            return curr->valoare;
        }
        curr = curr->next;
    }
    return NULL;
}

// 3. ȘTERGERE
void stergere(HashTable* ht, char* cheie) {
    int index = hashFunction(cheie);
    Node* curr = ht->buckets[index];
    Node* prev = NULL;
    
    while (curr != NULL) {
        if (strcmp(curr->cheie, cheie) == 0) {
            if (prev == NULL) {
                ht->buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("Cuvântul '%s' a fost șters din dicționar.\n", cheie);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Cuvântul '%s' nu a fost găsit pentru a fi șters.\n", cheie);
}

int main() {
    HashTable dictionar;
    initTable(&dictionar);

    // Testare funcționalități dicționar
    inserare(&dictionar, "masina", "Vehicul terestru cu motor propulsat pe roti.");
    inserare(&dictionar, "algoritm", "O succesiune finita de pasi pentru rezolvarea unei probleme.");
    inserare(&dictionar, "programare", "Actul de a scrie cod sursa pentru un calculator.");

    printf("\n--- CĂUTARE ---\n");
    char* def = cautare(&dictionar, "algoritm");
    if(def) printf("Definitie 'algoritm': %s\n", def);
    else printf("Cuvântul nu există.\n");

    printf("\n--- ȘTERGERE ---\n");
    stergere(&dictionar, "masina");

    printf("\n--- CĂUTARE DUPĂ ȘTERGERE ---\n");
    def = cautare(&dictionar, "masina");
    if(def) printf("Definitie 'masina': %s\n", def);
    else printf("Cuvântul 'masina' nu a fost găsit în dicționar.\n");

    return 0;
}
