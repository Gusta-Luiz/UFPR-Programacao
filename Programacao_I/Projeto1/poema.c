#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ()
{
    /* Abre o arquivo binario */
    FILE* arquivo = fopen("file.bin", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    /* Aponta o ponteiro para o fim do arquivo e anota seu tamanho */
    fseek(arquivo, 0, SEEK_END);
    int Fim = ftell(arquivo);
    if (Fim == -1) {
        printf("Erro ao ler o arquivo");
        exit(1);
    }
    /* Retorna o ponteiro ao inicio e aloca memoria para a string*/
    fseek(arquivo, 0, SEEK_SET);
    char* string = (char*) malloc(Fim);
    if (string == NULL) {
        printf("Erro ao alocar memoria");
        exit(1);
    }

    /* Realiza a leitura de 4 em 4 Bytes */
    int i = 0;
    int num;
    while (i < Fim) {
        /* Le 4 bytes para o int e o armazena em num*/
        fread(&num, 4, 1, arquivo);
        i += 4;

        /* Le 1 byte para o char e o adiciona a string na posicao num */
        char c;
        fread(&c, 1, 1, arquivo);
        string[num] = c;
        i += 1;
    }
    
    /* Imprime a string */
    printf("%s\n", string);
    
    /* Libera a memoria alocada */
    fclose (arquivo);
    free(string);
    exit(0);
}