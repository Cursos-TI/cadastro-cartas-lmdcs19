/*
 * Super Trunfo - Tema: Países
 * Cada país é dividido em 8 estados (A-H), cada estado com 4 cidades (1-4).
 * Código da carta: letra do estado + número da cidade (ex: A01, B03)
 *
 * Propriedades de cada cidade:
 *   - População
 *   - Área (km²)
 *   - PIB (em bilhões de reais)
 *   - Número de pontos turísticos
 *   - Densidade Populacional (calculada: população / área)
 *   - PIB per Capita (calculado: PIB / população)
 */

#include <stdio.h>

#define NUM_ESTADOS 8
#define CIDADES_POR_ESTADO 4
#define TOTAL_CARTAS (NUM_ESTADOS * CIDADES_POR_ESTADO)

/* Estrutura que representa uma carta (cidade) */
typedef struct {
    char codigo[4];                /* Ex: "A01" */
    char nome[50];
    long long populacao;
    double area;                   /* km² */
    double pib;                    /* em bilhões de reais */
    int pontos_turisticos;
    double densidade_populacional; /* hab/km² - calculado automaticamente */
    double pib_per_capita;         /* R$/hab  - calculado automaticamente */
} Carta;

/* Exibe o cabeçalho do programa */
void exibir_cabecalho() {
    printf("============================================\n");
    printf("      SUPER TRUNFO - TEMA: PAISES           \n");
    printf("============================================\n\n");
}

/* Exibe separador visual */
void exibir_separador() {
    printf("--------------------------------------------\n");
}

/* Calcula automaticamente densidade populacional e PIB per capita */
void calcular_propriedades(Carta *carta) {
    if (carta->area > 0)
        carta->densidade_populacional = (double)carta->populacao / carta->area;
    else
        carta->densidade_populacional = 0.0;

    if (carta->populacao > 0)
        /* PIB em bilhões → converter para reais (*1e9) antes de dividir */
        carta->pib_per_capita = (carta->pib * 1e9) / (double)carta->populacao;
    else
        carta->pib_per_capita = 0.0;
}

/* Cadastra os dados de uma carta via terminal */
void cadastrar_carta(Carta *carta, char estado, int numero) {
    /* Gera o código da carta automaticamente */
    carta->codigo[0] = estado;
    carta->codigo[1] = '0';
    carta->codigo[2] = '0' + numero;
    carta->codigo[3] = '\0';

    printf("\n>>> Cadastrando carta [%s] - Estado %c, Cidade %d <<<\n",
           carta->codigo, estado, numero);
    exibir_separador();

    printf("Nome da cidade: ");
    scanf(" %49[^\n]", carta->nome);

    printf("Populacao (habitantes): ");
    scanf("%lld", &carta->populacao);

    printf("Area (km2): ");
    scanf("%lf", &carta->area);

    printf("PIB (em bilhoes de reais): ");
    scanf("%lf", &carta->pib);

    printf("Numero de pontos turisticos: ");
    scanf("%d", &carta->pontos_turisticos);

    /* Calcula automaticamente as propriedades derivadas */
    calcular_propriedades(carta);
}

/* Exibe os dados de uma carta formatada */
void exibir_carta(const Carta *carta) {
    printf("\n  Carta: [%s]\n", carta->codigo);
    printf("  Cidade                 : %s\n",    carta->nome);
    printf("  Populacao              : %lld habitantes\n", carta->populacao);
    printf("  Area                   : %.2f km2\n", carta->area);
    printf("  PIB                    : R$ %.2f bilhoes\n", carta->pib);
    printf("  Pontos Turisticos      : %d\n", carta->pontos_turisticos);
    printf("  Densidade Populacional : %.2f hab/km2\n", carta->densidade_populacional);
    printf("  PIB per Capita         : R$ %.2f\n", carta->pib_per_capita);
}

int main() {
    Carta cartas[TOTAL_CARTAS];
    char estados[NUM_ESTADOS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int indice = 0;
    int i, j;

    exibir_cabecalho();

    printf("Este programa cadastra %d cartas de cidades.\n", TOTAL_CARTAS);
    printf("Organizadas em %d estados (A a H), com %d cidades cada.\n\n",
           NUM_ESTADOS, CIDADES_POR_ESTADO);

    /* ---- FASE DE CADASTRO ---- */
    printf("============================================\n");
    printf("           FASE DE CADASTRO                 \n");
    printf("============================================\n");

    for (i = 0; i < NUM_ESTADOS; i++) {
        printf("\n*** ESTADO %c ***\n", estados[i]);
        for (j = 1; j <= CIDADES_POR_ESTADO; j++) {
            cadastrar_carta(&cartas[indice], estados[i], j);
            indice++;
        }
    }

    /* ---- FASE DE EXIBIÇÃO ---- */
    printf("\n\n");
    printf("============================================\n");
    printf("        CARTAS CADASTRADAS                  \n");
    printf("============================================\n");

    for (i = 0; i < NUM_ESTADOS; i++) {
        printf("\n  *** ESTADO %c ***\n", estados[i]);
        exibir_separador();
        for (j = 0; j < CIDADES_POR_ESTADO; j++) {
            exibir_carta(&cartas[i * CIDADES_POR_ESTADO + j]);
        }
    }

    printf("\n============================================\n");
    printf("  Cadastro concluido! Total de cartas: %d   \n", TOTAL_CARTAS);
    printf("============================================\n\n");

    return 0;
}