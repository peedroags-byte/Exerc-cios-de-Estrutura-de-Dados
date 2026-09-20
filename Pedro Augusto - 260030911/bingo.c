#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS         5
#define COLUNAS        5
#define MAX_CARTELAS  50
#define LIVRE          0
#define MAX_TENTATIVAS 1000

typedef enum
{
    COLUNA_B = 0,
    COLUNA_I = 1,
    COLUNA_N = 2,
    COLUNA_G = 3,
    COLUNA_O = 4
} Coluna;

typedef struct
{
    int numeros[LINHAS][COLUNAS];
} Cartela;

static const char LETRAS[] = "BINGO";

int  gerarNumero(int minimo, int maximo);
int  minimoDaColuna(Coluna coluna);
int  maximoDaColuna(Coluna coluna);
int  ehEspacoLivre(int linha, int coluna);
int  numeroExiste(int cartela[LINHAS][COLUNAS], int coluna, int numero);
void gerarCartela(int cartela[LINHAS][COLUNAS]);
void ordenarColuna(int cartela[LINHAS][COLUNAS], int coluna);
void ordenarCartela(int cartela[LINHAS][COLUNAS]);
int  cartelasIguais(int a[LINHAS][COLUNAS], int b[LINHAS][COLUNAS]);
void copiarCartela(int origem[LINHAS][COLUNAS], int destino[LINHAS][COLUNAS]);
void imprimirCartela(int cartela[LINHAS][COLUNAS]);
int  lerQuantidade(void);

int gerarNumero(int minimo, int maximo)
{
    return minimo + rand() % (maximo - minimo + 1);
}

int minimoDaColuna(Coluna coluna)
{
    return (coluna * 15) + 1;
}

int maximoDaColuna(Coluna coluna)
{
    return (coluna + 1) * 15;
}

int ehEspacoLivre(int linha, int coluna)
{
    return (linha == 2 && coluna == COLUNA_N);
}

int numeroExiste(int cartela[LINHAS][COLUNAS], int coluna, int numero)
{
    int linha;

    for (linha = 0; linha < LINHAS; linha++)
    {
        if (cartela[linha][coluna] == numero)
        {
            return 1;
        }
    }

    return 0;
}

void gerarCartela(int cartela[LINHAS][COLUNAS])
{
    int linha, coluna, numero;

    for (linha = 0; linha < LINHAS; linha++)
    {
        for (coluna = 0; coluna < COLUNAS; coluna++)
        {
            cartela[linha][coluna] = LIVRE;
        }
    }

    for (coluna = COLUNA_B; coluna <= COLUNA_O; coluna++)
    {
        for (linha = 0; linha < LINHAS; linha++)
        {
            if (ehEspacoLivre(linha, coluna))
            {
                cartela[linha][coluna] = LIVRE;
                continue;
            }

            do
            {
                numero = gerarNumero(minimoDaColuna((Coluna) coluna),
                                     maximoDaColuna((Coluna) coluna));
            }
            while (numeroExiste(cartela, coluna, numero));

            cartela[linha][coluna] = numero;
        }
    }
}

void ordenarColuna(int cartela[LINHAS][COLUNAS], int coluna)
{
    int valores[LINHAS];
    int total = 0;
    int i, j, menor, troca;

    for (i = 0; i < LINHAS; i++)
    {
        if (!ehEspacoLivre(i, coluna))
        {
            valores[total++] = cartela[i][coluna];
        }
    }

    for (i = 0; i < total - 1; i++)
    {
        menor = i;

        for (j = i + 1; j < total; j++)
        {
            if (valores[j] < valores[menor])
            {
                menor = j;
            }
        }

        troca          = valores[i];
        valores[i]     = valores[menor];
        valores[menor] = troca;
    }

    total = 0;

    for (i = 0; i < LINHAS; i++)
    {
        if (!ehEspacoLivre(i, coluna))
        {
            cartela[i][coluna] = valores[total++];
        }
    }
}

void ordenarCartela(int cartela[LINHAS][COLUNAS])
{
    int coluna;

    for (coluna = COLUNA_B; coluna <= COLUNA_O; coluna++)
    {
        ordenarColuna(cartela, coluna);
    }
}

int cartelasIguais(int a[LINHAS][COLUNAS], int b[LINHAS][COLUNAS])
{
    int linha, coluna;

    for (linha = 0; linha < LINHAS; linha++)
    {
        for (coluna = 0; coluna < COLUNAS; coluna++)
        {
            if (a[linha][coluna] != b[linha][coluna])
            {
                return 0;
            }
        }
    }

    return 1;
}

void copiarCartela(int origem[LINHAS][COLUNAS], int destino[LINHAS][COLUNAS])
{
    int linha, coluna;

    for (linha = 0; linha < LINHAS; linha++)
    {
        for (coluna = 0; coluna < COLUNAS; coluna++)
        {
            destino[linha][coluna] = origem[linha][coluna];
        }
    }
}

void imprimirCartela(int cartela[LINHAS][COLUNAS])
{
    int linha, coluna;
    char texto[4];

    for (coluna = 0; coluna < COLUNAS; coluna++)
    {
        printf("%2c", LETRAS[coluna]);

        if (coluna < COLUNAS - 1)
        {
            printf("   ");
        }
    }

    printf("\n\n");

    for (linha = 0; linha < LINHAS; linha++)
    {
        for (coluna = 0; coluna < COLUNAS; coluna++)
        {
            if (cartela[linha][coluna] == LIVRE)
            {
                sprintf(texto, "X");
            }
            else
            {
                sprintf(texto, "%d", cartela[linha][coluna]);
            }

            printf("%2s", texto);

            if (coluna < COLUNAS - 1)
            {
                printf("   ");
            }
        }

        printf("\n");
    }
}

int lerQuantidade(void)
{
    int quantidade = 0;
    int lidos;

    do
    {
        printf("Quantas cartelas deseja gerar (1 a %d)? ", MAX_CARTELAS);
        lidos = scanf("%d", &quantidade);

        if (lidos != 1)
        {
            while (getchar() != '\n');
            quantidade = 0;
        }

        if (quantidade < 1 || quantidade > MAX_CARTELAS)
        {
            printf("Valor invalido. Tente novamente.\n\n");
        }
    }
    while (quantidade < 1 || quantidade > MAX_CARTELAS);

    return quantidade;
}

int main(void)
{
    int cartelas[MAX_CARTELAS][LINHAS][COLUNAS];
    Cartela vetorCartelas[MAX_CARTELAS];

    int quantidade;
    int i, j;
    int repetida;
    int tentativas;

    srand((unsigned int) time(NULL));

    printf("=== Gerador de Cartelas de Bingo ===\n\n");

    quantidade = lerQuantidade();

    for (i = 0; i < quantidade; i++)
    {
        tentativas = 0;

        do
        {
            repetida = 0;

            gerarCartela(cartelas[i]);
            ordenarCartela(cartelas[i]);

            for (j = 0; j < i; j++)
            {
                if (cartelasIguais(cartelas[i], cartelas[j]))
                {
                    repetida = 1;
                    break;
                }
            }

            tentativas++;
        }
        while (repetida && tentativas < MAX_TENTATIVAS);

        copiarCartela(cartelas[i], vetorCartelas[i].numeros);
    }

    for (i = 0; i < quantidade; i++)
    {
        printf("\n--- Cartela %d ---\n\n", i + 1);
        imprimirCartela(vetorCartelas[i].numeros);
    }

    printf("\n%d cartela(s) gerada(s) com sucesso.\n", quantidade);

    return 0;
}
