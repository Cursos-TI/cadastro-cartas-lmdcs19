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
 *   - Super Poder (soma de todas as propriedades)
 *
 * Regras de comparação:
 *   - Densidade Populacional: vence o MENOR valor
 *   - Demais propriedades:    vence o MAIOR valor
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
    double super_poder;            /* soma de todas as propriedades       */
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

/* Calcula automaticamente densidade populacional, PIB per capita e Super Poder */
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

    /* Super Poder: soma de todas as propriedades numericas */
    carta->super_poder = (double)carta->populacao
                       + carta->area
                       + carta->pib
                       + (double)carta->pontos_turisticos
                       + carta->densidade_populacional
                       + carta->pib_per_capita;
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
    printf("  Super Poder            : %.2f\n", carta->super_poder);
}

/* Retorna string indicando o vencedor de uma propriedade (maior vence) */
const char *resultado_maior(double v1, double v2, const char *cod1, const char *cod2) {
    if (v1 > v2)  return cod1;
    if (v2 > v1)  return cod2;
    return "EMPATE";
}

/* Retorna string indicando o vencedor de uma propriedade (menor vence) */
const char *resultado_menor(double v1, double v2, const char *cod1, const char *cod2) {
    if (v1 < v2)  return cod1;
    if (v2 < v1)  return cod2;
    return "EMPATE";
}

/* Exibe comparação completa entre duas cartas */
void comparar_cartas(const Carta *c1, const Carta *c2) {
    printf("\n");
    printf("============================================\n");
    printf("     COMPARACAO: [%s] vs [%s]              \n", c1->codigo, c2->codigo);
    printf("============================================\n");
    printf("  %-26s [%s] %-15lld | [%s] %-15lld | VENCEDOR: %s\n",
           "Populacao (hab):",
           c1->codigo, c1->populacao,
           c2->codigo, c2->populacao,
           resultado_maior((double)c1->populacao, (double)c2->populacao, c1->codigo, c2->codigo));

    printf("  %-26s [%s] %-15.2f | [%s] %-15.2f | VENCEDOR: %s\n",
           "Area (km2):",
           c1->codigo, c1->area,
           c2->codigo, c2->area,
           resultado_maior(c1->area, c2->area, c1->codigo, c2->codigo));

    printf("  %-26s [%s] %-15.2f | [%s] %-15.2f | VENCEDOR: %s\n",
           "PIB (bi R$):",
           c1->codigo, c1->pib,
           c2->codigo, c2->pib,
           resultado_maior(c1->pib, c2->pib, c1->codigo, c2->codigo));

    printf("  %-26s [%s] %-15d | [%s] %-15d | VENCEDOR: %s\n",
           "Pontos Turisticos:",
           c1->codigo, c1->pontos_turisticos,
           c2->codigo, c2->pontos_turisticos,
           resultado_maior((double)c1->pontos_turisticos, (double)c2->pontos_turisticos,
                           c1->codigo, c2->codigo));

    printf("  %-26s [%s] %-15.2f | [%s] %-15.2f | VENCEDOR: %s  (*menor vence)\n",
           "Densidade Pop. (hab/km2):",
           c1->codigo, c1->densidade_populacional,
           c2->codigo, c2->densidade_populacional,
           resultado_menor(c1->densidade_populacional, c2->densidade_populacional,
                           c1->codigo, c2->codigo));

    printf("  %-26s [%s] %-15.2f | [%s] %-15.2f | VENCEDOR: %s\n",
           "PIB per Capita (R$):",
           c1->codigo, c1->pib_per_capita,
           c2->codigo, c2->pib_per_capita,
           resultado_maior(c1->pib_per_capita, c2->pib_per_capita, c1->codigo, c2->codigo));

    printf("  %-26s [%s] %-15.2f | [%s] %-15.2f | VENCEDOR: %s\n",
           "Super Poder:",
           c1->codigo, c1->super_poder,
           c2->codigo, c2->super_poder,
           resultado_maior(c1->super_poder, c2->super_poder, c1->codigo, c2->codigo));

    printf("============================================\n");

    /* --- Placar de vitórias por propriedade --- */
    {
        int vit1 = 0, vit2 = 0, empates = 0;
        const char *venc;

        /* Populacao */
        venc = resultado_maior((double)c1->populacao, (double)c2->populacao, c1->codigo, c2->codigo);
        if      (venc == c1->codigo) vit1++;
        else if (venc == c2->codigo) vit2++;
        else empates++;

        /* Area */
        venc = resultado_maior(c1->area, c2->area, c1->codigo, c2->codigo);
        if      (venc == c1->codigo) vit1++;
        else if (venc == c2->codigo) vit2++;
        else empates++;

        /* PIB */
        venc = resultado_maior(c1->pib, c2->pib, c1->codigo, c2->codigo);
        if      (venc == c1->codigo) vit1++;
        else if (venc == c2->codigo) vit2++;
        else empates++;

        /* Pontos Turisticos */
        venc = resultado_maior((double)c1->pontos_turisticos, (double)c2->pontos_turisticos,
                               c1->codigo, c2->codigo);
        if      (venc == c1->codigo) vit1++;
        else if (venc == c2->codigo) vit2++;
        else empates++;

        /* Densidade Populacional (menor vence) */
        venc = resultado_menor(c1->densidade_populacional, c2->densidade_populacional,
                               c1->codigo, c2->codigo);
        if      (venc == c1->codigo) vit1++;
        else if (venc == c2->codigo) vit2++;
        else empates++;

        /* PIB per Capita */
        venc = resultado_maior(c1->pib_per_capita, c2->pib_per_capita, c1->codigo, c2->codigo);
        if      (venc == c1->codigo) vit1++;
        else if (venc == c2->codigo) vit2++;
        else empates++;

        /* Super Poder */
        venc = resultado_maior(c1->super_poder, c2->super_poder, c1->codigo, c2->codigo);
        if      (venc == c1->codigo) vit1++;
        else if (venc == c2->codigo) vit2++;
        else empates++;

        /* Exibe placar */
        printf("\n  PLACAR FINAL\n");
        printf("  [%s] %-20s : %d vitoria(s)\n", c1->codigo, c1->nome, vit1);
        printf("  [%s] %-20s : %d vitoria(s)\n", c2->codigo, c2->nome, vit2);
        if (empates > 0)
            printf("  Empates                        : %d\n", empates);
        printf("\n");

        if (vit1 > vit2)
            printf("  *** CARTA VENCEDORA: [%s] - %s! ***\n", c1->codigo, c1->nome);
        else if (vit2 > vit1)
            printf("  *** CARTA VENCEDORA: [%s] - %s! ***\n", c2->codigo, c2->nome);
        else
            printf("  *** RESULTADO FINAL: EMPATE! ***\n");

        printf("============================================\n");
    }
}

/* Busca uma carta pelo código (ex: "A01"). Retorna NULL se não encontrar. */
const Carta *buscar_carta(const Carta cartas[], int total, const char *codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (cartas[i].codigo[0] == codigo[0] &&
            cartas[i].codigo[1] == codigo[1] &&
            cartas[i].codigo[2] == codigo[2]) {
            return &cartas[i];
        }
    }
    return NULL;
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

    /* ---- FASE DE COMPARAÇÃO ---- */
    {
        char cod1[4], cod2[4];
        char continuar;
        const Carta *carta1;
        const Carta *carta2;

        printf("============================================\n");
        printf("         FASE DE COMPARACAO                 \n");
        printf("============================================\n");
        printf("  Formato do codigo: letra + dois digitos\n");
        printf("  Exemplos: A01, B03, H04\n\n");

        do {
            printf("Digite o codigo da primeira carta : ");
            scanf(" %3s", cod1);

            printf("Digite o codigo da segunda carta  : ");
            scanf(" %3s", cod2);

            carta1 = buscar_carta(cartas, TOTAL_CARTAS, cod1);
            carta2 = buscar_carta(cartas, TOTAL_CARTAS, cod2);

            if (carta1 == NULL) {
                printf("  [!] Carta '%s' nao encontrada. Tente novamente.\n\n", cod1);
                continue;
            }
            if (carta2 == NULL) {
                printf("  [!] Carta '%s' nao encontrada. Tente novamente.\n\n", cod2);
                continue;
            }
            if (carta1 == carta2) {
                printf("  [!] Escolha duas cartas diferentes.\n\n");
                continue;
            }

            comparar_cartas(carta1, carta2);

            printf("\nDeseja comparar outras cartas? (s/n): ");
            scanf(" %c", &continuar);
            printf("\n");

        } while (continuar == 's' || continuar == 'S');
    }

    printf("Obrigado por jogar Super Trunfo - Paises!\n\n");

    return 0;
}