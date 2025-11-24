#include <stdio.h>
#include <string.h>

#define MAX 5
#define TAM 50

// Definição da struct Territorio
typedef struct {
    char nome[TAM];
    char cor[TAM];
    int tropas;
} Territorio;

int main() {

    Territorio mapa[MAX];

    printf("=== CADASTRO INICIAL DE TERRITÓRIOS (WAR – Nível Novato) ===\n\n");

    for (int i = 0; i < MAX; i++) {
        printf("Território %d:\n", i + 1);

        // Nome do território
        printf("Digite o nome: ");
        fgets(mapa[i].nome, TAM, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        // Cor do exército
        printf("Digite a cor do exército: ");
        fgets(mapa[i].cor, TAM, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        // Número de tropas
        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[i].tropas);

        getchar(); // limpa o buffer após scanf

        printf("\n");
    }

    // Exibição final
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < MAX; i++) {
        printf("Território %d:\n", i + 1);
        printf(" Nome: %s\n", mapa[i].nome);
        printf(" Cor do Exército: %s\n", mapa[i].cor);
        printf(" Tropas: %d\n\n", mapa[i].tropas);
    }

    return 0;
}
