#include <stdio.h>

typedef unsigned char byte;   
typedef int inteiro;          
typedef float real;           

int main() {

    byte idade = 25;
    inteiro quantidade = 100;
    real temperatura = 36.7;

    printf("Idade (byte): %u\n", idade);
    printf("Quantidade (inteiro): %d\n", quantidade);
    printf("Temperatura (real): %.2f\n", temperatura);

    return 0;
}
