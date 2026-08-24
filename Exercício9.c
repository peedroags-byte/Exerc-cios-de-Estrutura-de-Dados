#include <stdio.h>
#include <stdint.h>

#define MAX_ALUNOS 40
#define MAX_PRODUTOS 500
#define ANO_ATUAL 2026

typedef float real;

int main() {
    uint8_t alunos = 35;       
    int32_t estoque = 450;     
    real temperatura = 22.5;   

    printf("Ano atual: %d\n", ANO_ATUAL);
    printf("Máximo de alunos: %d, alunos cadastrados: %u\n", MAX_ALUNOS, alunos);
    printf("Máximo de produtos: %d, produtos em estoque: %d\n", MAX_PRODUTOS, estoque);
    printf("Temperatura ambiente: %.2f °C\n", temperatura);

    return 0;
}