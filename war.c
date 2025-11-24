#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD 5
#define TAM 50

// -------------------------------------------
// Estruturas
// -------------------------------------------
typedef struct {
    char nome[TAM];
    char cor[TAM];
    int tropas;
} Territorio;

typedef enum {
    MISSAO_DESTRUIR_VERDE = 1,
    MISSAO_CONQUISTAR_3 = 2
} TipoMissao;


// -------------------------------------------
// Funções de inicialização
// -------------------------------------------
void inicializarTerritorios(Territorio *mapa) {
    const char *nomes[] = {"America", "Europa", "Asia", "Africa", "Oceania"};
    const char *cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"};

    for (int i = 0; i < QTD; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i % 5]);
        mapa[i].tropas = (rand() % 3) + 1;  // 1 a 3 tropas
    }
}

TipoMissao gerarMissao() {
    return (rand() % 2) + 1;  // 1 ou 2
}

// -------------------------------------------
// Função de ataque
// -------------------------------------------
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n Dados:\n");
    printf(" Atacante (%s): %d\n", atacante->nome, dadoAtk);
    printf(" Defensor  (%s): %d\n\n", defensor->nome, dadoDef);

    if (dadoAtk >= dadoDef) {
        defensor->tropas--;
        printf(" Atacante venceu! Defensor perdeu 1 tropa.\n");

        if (defensor->tropas <= 0) {
            printf("Território %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }

    } else {
        atacante->tropas--;
        printf(" Defensor venceu! Atacante perdeu 1 tropa.\n");
    }
}


// -------------------------------------------
// Funções de exibição
// -------------------------------------------
void mostrarMapa(const Territorio *mapa) {
    printf("\n========== MAPA ATUAL ==========\n");
    for (int i = 0; i < QTD; i++) {
        printf("Território %d:\n", i + 1);
        printf(" Nome: %s\n", mapa[i].nome);
        printf(" Cor: %s\n", mapa[i].cor);
        printf(" Tropas: %d\n\n", mapa[i].tropas);
    }
}

void mostrarMissao(const TipoMissao missao) {
    printf("\n Sua missão: ");
    if (missao == MISSAO_DESTRUIR_VERDE)
        printf("Destruir todo o exército Verde.\n");
    else
        printf("Conquistar 3 territórios.\n");
}

// -------------------------------------------
// Verificação de missão
// -------------------------------------------
int verificarMissao(const Territorio *mapa, const TipoMissao missao) {

    if (missao == MISSAO_DESTRUIR_VERDE) {
        for (int i = 0; i < QTD; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0)
                return 0; // missão ainda não cumprida
        }
        return 1;
    }

    if (missao == MISSAO_CONQUISTAR_3) {
        int count = 0;
        for (int i = 0; i < QTD; i++) {
            if (strcmp(mapa[i].cor, mapa[0].cor) == 0) // assume jogador é cor do território 1
                count++;
        }
        return count >= 3;
    }

    return 0;
}


int main() {

    srand(time(NULL));

    Territorio *mapa = (Territorio *)calloc(QTD, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    inicializarTerritorios(mapa);

    TipoMissao missao = gerarMissao();

    int opcao, atk, def;

    do {
        mostrarMapa(mapa);
        mostrarMissao(missao);

        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: // ataque
                printf("Selecione o atacante (1–5): ");
                scanf("%d", &atk);

                printf("Selecione o defensor (1–5): ");
                scanf("%d", &def);

                if (atk < 1 || atk > 5 || def < 1 || def > 5 || atk == def) {
                    printf(" Entrada inválida!\n");
                } else {
                    atacar(&mapa[atk - 1], &mapa[def - 1]);
                }
                break;

            case 2: // verificar missão
                if (verificarMissao(mapa, missao)) {
                    printf("\n PARABÉNS! Você cumpriu sua missão!\n");
                } else {
                    printf("\n Missão ainda não cumprida.\n");
                }
                break;

            case 3:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);

    free(mapa);
    return 0;
}
