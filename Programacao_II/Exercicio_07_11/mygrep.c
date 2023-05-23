#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Crie um programa que simule o comando "grep -c" do UNIX
/* que imprime a quantidade de ocorrencias de uma certa string */

void main (int argc, char *argv[])
{
    /* Verifica o numero de comandos inseridos */
    if (argc != 3) {
        printf("Numero incorreto de comandos \nUso correto: %s <string> <arquivo>\n", argv[0]);
        exit(1);
    }
    /* Copia a entrada para variaveis */
    char *arquivo_nome = argv[1];
    char *string_grep = argv[2];
    
    /* Le o arquivo indicado e retorna um ponteiro para o stream */    
    FILE *arquivo = fopen(arquivo_nome, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    /* Chega ao final do arquivo */
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        printf("Erro ao chegar ao final do arquivo\n");
        exit(1);
    }
    /* Retorna o numero de bytes do arquivo */
    long int tamanho_arquivo = ftell(arquivo);
    if (tamanho_arquivo == -1L) {
        printf("Erro ao retornar o tamanho do arquivo\n");
        exit(1);
    }
    /* Retorna o ponteiro para o inicio do arquivo */
    if (fseek(arquivo, 0, SEEK_SET) != 0) {
        printf("Erro ao retornar o ponteiro para o inicio do arquivo\n");
        exit(1);
    }
    /* Aloca memoria para o conteudo do arquivo */
    char *conteudo_arquivo = (char *) malloc(tamanho_arquivo);
    if (conteudo_arquivo == NULL) {
        printf("Erro ao alocar memoria para o conteudo do arquivo\n");
        exit(1);
    }
    /* Le o conteudo do arquivo na memoria */
    if (fread(conteudo_arquivo, 1, tamanho_arquivo, arquivo) != tamanho_arquivo) {
        printf("Erro ao ler o conteudo do arquivo\n");
        exit(1);
    }
    /* Fecha o arquivo */
    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo\n");
        exit(1);
    }
    /* Conta a quantidade de ocorrencias da string_grep no conteudo do arquivo */
    int quantidade_ocorrencias = 0;
    char *posicao_ocorrencia = conteudo_arquivo;
    /* Enquanto houver ocorrencias da string_grep no conteudo do arquivo */
    while ((posicao_ocorrencia = strstr(posicao_ocorrencia, string_grep)) != NULL) {
        quantidade_ocorrencias++;
        posicao_ocorrencia += strlen(string_grep);
    }
    /* Imprime a quantidade de ocorrencias da string_grep no conteudo do arquivo */
    printf("%d Ocorrencias da string %s no arquivo %s\n", quantidade_ocorrencias, string_grep, arquivo_nome);

    /* Libera a memoria alocada para o conteudo do arquivo */
    free(conteudo_arquivo);
    
    return;
}