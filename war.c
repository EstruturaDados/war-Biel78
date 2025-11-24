#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD 5
#define TAM 50

typedef struct {
    char nome[TAM];
    char cor[TAM];
    int tropas;
} Territorio;

// ------------------------------------------------------
// Função que simula um ataque entre dois territórios
// ------------------------------------------------------
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n Dados:\n");
    printf(" Atacante (%s): %d\n", atacante->nome, dadoAtk);
    printf(" Defensor  (%s): %d\n\n", defensor->nome, dadoDef);

    // Empates favorecem o atacante
    if (dadoAtk >= dadoDef) {
        defensor->tropas--;
        printf(" Atacante venceu! Defensor perde 1 tropa.\n");

        if (defensor->tropas <= 0) {
            printf("🏳 Território %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }

    } else {
        atacante->tropas--;
        printf(" Defensor venceu! Atacante perde 1 tropa.\n");
    }

    printf("----------------------------------------\n");
}

// ------------------------------------------------------
// Exibe o estado atual do mapa
// ------------------------------------------------------
void mostrarMapa(Territorio *mapa) {
    printf("\n========== MAPA ATUAL ==========\n");
    for (int i = 0; i < QTD; i++) {
        printf("Território %d:\n", i + 1);
        printf(" Nome: %s\n", mapa[i].nome);
        printf(" Cor: %s\n", mapa[i].cor);
        printf(" Tropas: %d\n\n", mapa[i].tropas);
    }
}

int main() {

    srand(time(NULL)); // necessário para números aleatórios

    // Alocação dinâmica com calloc
    Territorio *mapa = (Territorio *)calloc(QTD, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    const char *nomes[] = {"America", "Europa", "Asia", "Africa", "Oceania"};

    printf("=== CADASTRO DOS TERRITÓRIOS ===\n\n");

    for (int i = 0; i < QTD; i++) {
        strcpy(mapa[i].nome, nomes[i]);

        printf("Território %d: %s\n", i + 1, mapa[i].nome);

        printf("Cor do exército: ");
        fgets(mapa[i].cor, TAM, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();

        printf("\n");
    }

    int atk, def;

    // ------------------------------- LOOP DE ATAQUE -------------------------------
    while (1) {

        mostrarMapa(mapa);

        printf("Escolha o atacante (1–5) ou 0 para sair: ");
        scanf("%d", &atk);

        if (atk == 0) break;

        printf("Escolha o defensor (1–5): ");
        scanf("%d", &def);
        getchar();

        if (atk < 1 || atk > 5 || def < 1 || def > 5 || atk == def) {
            printf(" Entrada inválida!\n");
            continue;
        }

        atacar(&mapa[atk - 1], &mapa[def - 1]);
    }

    // Liberação da memória
    free(mapa);

    printf("\nJogo encerrado.\n");
    return 0;
}
