/* Programa criado em 11/2022 por Luiz Gustavo Dalmaz Paquete*/

struct artigos_t {
    char *titulo;               /* Titulo da revista ou artigo */
    char *ano;                  /* Ano de publicacao */
    char *classe;               /* Classe de artigo, entre A1 a C */
} typedef artigos;

struct pesquisador_t {
    char *nome;                 /* Nome do pesquisador */
 /* char *grupo; */             /* Grupo de pesquisa do pesquisador */
    int num_periodicos;         /* Numero de artigos publicados */
    artigos *periodicos;        /* Vetor de periodicos */
    int num_conferencias;       /* Numero de conferencias */
    artigos *conferencias;      /* Vetor de conferencias */
} typedef pesquisador;

struct lista_qualis_t {
    char **strings;             /* Vetor de qualis */
    int num_total;              /* Numero de qualis */
} typedef lista_qualis;

struct lista_pesquisadores_t {
    pesquisador **pesquisadores; /* Vetor de pesquisadores */
    int num_total;               /* Numero de pesquisadores */
} typedef lista_pesquisadores;

/* Recebe a entrada de "main" e analisa seus argumentos para que correspondam a chamada 
 * Retorna 1 em caso de sucesso, ou 0 em erro */
int testa_entrada(int argc, char *argv[], char **curriculo, char **conferencias, char **artigos);

/* Recebe o nome ou diretorio do arquivo, entao aloca e armazena seu conteudo na memoria 
 * Retorna um ponteiro para o conteudo do arquivo */
char *leitura_arq(char *nome_arquivo);

/* Recebe uma string separada por "\n", a separa em sub-strings, remove repeticoes
 * Aloca uma nova lista de artigos e armazena cada linha nesta lista */
lista_qualis *listagem_str(char *str);

/* Limpa todos os dados alocados na lista de artigos 
 * Em seguida limpa a propria struct, retorna 1 em sucesso, 0 o contrario */
int limpa_lista(lista_qualis *lista);

/* Aloca espaco para um nova struct de pesquisador e a preenche com alguns dados 
 * Retorna um ponteiro para esta struct */
pesquisador *cria_pesquisador(char *nome);

/* Limpa os dados alocados na lista de artigos de um certo pesquisador 
 * E em seguida limpa a propria struct, retorna 1 em sucesso, ou 0 o contrario */
int limpa_pesquisadores(lista_pesquisadores *pesquisador);

/* Recebe uma string onde ira ser procurado a string "alvo", que antecede nossa resposta,
 * entao encontra esta resposta (que esta entre " ") e a retorna */
char *encontra_str(char **str, char *alvo);

/* Recebe uma string qualquer e a retorna totalmente em maiusculo */
int maiusculo_str(char *Str);

/* Recebe o titulo de um artigo e o compara com o arquivo original de qualis 
 * Retorna o titulo que mais se assemelha ao original, ou o original caso a distancia > 11 */
int checa_artigo(char **titulo, char **classe, lista_qualis *lista);

/* Recebe os dados para a criacao de um novo artigo e o autor do mesmo,
 * Aloca o espaco necessario e retorna 1 em sucesso, 0 o contrario */
int cria_artigo(pesquisador *autor, char *titulo, char *ano, char *classe, char *tipo);

/* Salva todos os artigos, separados por classe em uma lista */
lista_qualis *salva_lista_estrato(lista_pesquisadores *lista, char *classe, char *tipo);

/* Imprime todos os artigos, separados por classe */
/* Imprime os periodicos por estrato */
void imprime_estratos(lista_pesquisadores *vetor_autores);

/* Recebe uma lista de strings, conta a ocorrencia de cada string e adiciona o numero ao final da string 
 * Entao remove strings duplicadas da lista */
void conta_ocorrencias(lista_qualis *lista);


/* Recebe uma lista de strings, conta a ocorrencia de cada string e adiciona o numero ao final da string 
 * Entao remove strings duplicadas da lista */
void conta_e_remove(lista_qualis *lista);

/* Imprime a ocorrencia de cada classe de um autor */
void imprime_autor(pesquisador *autor);