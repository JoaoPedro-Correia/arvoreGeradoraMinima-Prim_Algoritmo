//!!AS VARIAVEIS QUE ARMAZENAM A MATRICULA SÃO CHAMADAS DE 'ID'

/*PRE-PROCESSAMENTO DAS FUNCOES IMPORTADAS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*CHAMO A BIBLIOTECA DA LISTA*/
/*list.h TEM DUAS ESTRUTURAS,
 * NODE E LIST*/
#include "cidades.h"
#include "list.h"
#include "node.c"

long int contar_linhas(char *file_name);
/*REMOVE A QUEBRA DE LINHA DO ARRAY DE CHAR*/
void remove_line_break(char *n);
/*ADICIONO O ESTUDANTE DO ARQUIVO NA LISTA*/
void get_file_element(List *l, FILE *fl);
/*LER AQUIVO*/
void read_file(List *, char *, long int); // Lista e o NOME do arquivo
/*LIMPO O TERMINAL*/
void clear_window(void);
/*LIMPO O BUFFER DO COMPUTADOR*/
void clear_buff(void);
/*PRINTA TODOS OS ELEMENTOS DA LISTA*/
void list_print(List *l);
/*EXIBE A LISTA NA TELA EM SUA POSIÇÃO NA TABELA HASH*/
void printMatriz(List *);
void printList(List *list);

void escolherCidadeInicial(List *list, int *menorCaminho);

void printListaCidades();
void printMenorCaminho(int *caminho);
int primAlgoritmo(List *list, int *menorCaminho);

long int lines;
/*------------------------------------------------------------*/
// PASSO O NOME DO ARQUIVO PARA *argv
int main(int argc, char *argv[]) {
  int option;
  List *list;

  char arquivo[] = "cidades.txt";

  lines = contar_linhas(arquivo); // QUANTIDADE DE CIDADES
  int menorCaminho[lines];

  /*CRIA UM ARRAY DE LISTA*/
  list = list_new_vector(lines); // CRIO O ARRYLIST

  read_file(list, arquivo, lines); // LER ARQUIVO

  // printMatriz(list);

  int pesoTotal = primAlgoritmo(list, menorCaminho);

  printMenorCaminho(menorCaminho);
  printf("Peso Total: %d", pesoTotal);
  /*DESALOCO TODO ARRAY E SEUS ALEMENTOS*/
  list_clear_vector(list, lines);
  return 0;
}

void printMenorCaminho(int *caminho) {
  int i;
  for (i = 1; i <= lines; i++) {
    printf("%d - ", caminho[i]);
    printCidade(caminho[i]);
    printf("\n");
  }
}

void escolherCidadeInicial(List *list, int *menorCaminho) {
  int opcao;

  printf("---Escolha a cidade inicial---\n");
  printListaCidades();
  printf("Opcao: ");
  scanf("%d", &opcao);

  menorCaminho[0] = opcao;
}
/*------------------------------------------------------------*/
long int contar_linhas(char *file_name) {
  FILE *fl = fopen(file_name, "r"); // ABRIR ARQUIVO PARA LEITURA
  char aux[100];
  long int i = 0; // VAI ARMAZENAR A QUANTIDADE DE LINHAS

  if (!fl) { // CASO NAO CONSIGA ABRI-LO
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  while (!feof(fl)) {
    fgets(aux, 100, fl);
    i++; // CONTA AS LINHAS
  }
  --i;

  fclose(fl);
  return i; // RETORNA A QUANTIDADE DE ALUNOS
}

/*------------------------------------------------------------*/
void remove_line_break(char *n) {
  int len;
  len = strlen(n);
  if (n[len - 1] == '\n')
    n[--len] = 0; // remove '\n' e actualiza len
}

/*------------------------------------------------------------*/
void get_file_element(List *l, FILE *fl) {
  int origem, destino, distancia;

  // ARMAZENO A MATRICULA
  fscanf(fl, "%d", &origem);
  // remove_line_break(id_student);

  fscanf(fl, "%d", &destino);

  // ARMAZENO O NOME
  fscanf(fl, "%d", &distancia);
  // remove_line_break(student_name);

  // ADICIONO NA LISTA O NOME E A MATRICULA
  list_add(&l[origem - 1], destino, distancia);
}

/*------------------------------------------------------------*/
void read_file(List *l, char *file_name,
               long int line) { // Lista e o NOME do arquivo

  FILE *fl = fopen(file_name, "r");
  int i = 0;
  if (!fl) {
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  while (!feof(fl)) {
    get_file_element(l, fl);
    i++;
  }

  fclose(fl);

  printf("Leitura de arquivo concluida\n");
}

/*------------------------------------------------------------*/
void clear_buff() {
  int c;
  while ((c = getchar()) != '\n') {
  }
}

/*------------------------------------------------------------*/
int **initVetor() {
  int i, e;
  int **vetor;

  vetor = (int **)malloc(lines * sizeof(int *));
  for (i = 0; i < lines; i++) {
    vetor[i] = (int *)malloc(lines * sizeof(int));
  }

  for (i = 0; i < lines; i++) {
    for (e = 0; e < lines; e++) {
      vetor[i][e] = 0;
    }
  }

  return vetor;
}

/*------------------------------------------------------------*/
void listForVetor(List *list, int **vetor) {
  int i;

  for (i = 0; i < lines; i++) {
    Node *no = get_first_element(&list[i]);
    while (!node_empty(no)) {
      vetor[i][get_id(no) - 1] = get_distancia(no);
      no = node_next(no);
    }
  }
}

/*------------------------------------------------------------*/
void freeVetor(int **vetor) {
  int i;

  for (i = 0; i < lines; i++) {
    free(vetor[i]);
  }
  free(vetor);
}

/*------------------------------------------------------------*/
void printMatriz(List *list) {
  int i, e; // CONTADOR
  int **vetor;

  vetor = initVetor();

  listForVetor(list, vetor);

  printf("\n\n====================Vetor=========================\n");
  for (i = 0; i < lines; i++) { // ANDO PELA TABELA
    for (e = 0; e < lines; e++) {
      printf("|%d", vetor[i][e]);
    }
    printf("\n");
  }

  freeVetor(vetor);
}

/*------------------------------------------------------------*/
void list_print(List *l) {
  Node *n = get_first_element(l);
  while (!node_empty(n)) { // PERCORRE TODOS OS ELEMENTOS DA LISTA
    printf("\n [%d, %d]", get_id(n), get_distancia(n));
    n = node_next(n);
  } // EXIBE O INDICE DO ARRAY
}

/*------------------------------------------------------------*/
void printList(List *list) {
  int i; // CONTADOR

  printf("\n\n==========LISTA=============\n");
  for (i = 0; i < lines; i++) { // ANDO PELA TABELA
    printf("\n(%d)", i + 1);
    list_print(&list[i]); // EXIBE A LISTA DO INDICE i
  }
}

/*------------------------------------------------------------*/
void printListaCidades() {
  int i;
  for (i = 1; i <= lines; i++) {
    printf("%d - ", i);
    printCidade(i);
    printf("\n");
  }
}

/*------------------------------------------------------------*/
int verificarCidadesVisitadas(int cidadeCandidata, int *cidades, int qntd) {
  int i;
  for (i = 0; i < qntd; i++) {
    if (cidades[i] == cidadeCandidata) {
      return 0;
    }
  }
  return 1;
}

/*------------------------------------------------------------*/
// RETORNA A CIDADE MAIS PERTA E
// QUE NAO FOI VISITADA AINDA DO NO
int buscarMenorCaminho(Node *no, int *cidades, int qntd, int *distPercorrida) {
  int cidadeProxima = 9999;

  for (; node_empty(no); no = node_next(no)) {
    if (get_distancia(no) < cidadeProxima) {
      if (verificarCidadesVisitadas(get_id(no), cidades,
                                    qntd)) { // CIDADE NAO FOI SELECIONADA
        cidadeProxima = get_id(no);
        *distPercorrida = get_distancia(no);
      }
    }
  }
  return cidadeProxima;
}

/*------------------------------------------------------------*/
int buscarCidadeProxima(List *list, int *cidades, int qntd,
                        int *distPercorrida) {
  int i;
  int distCandidata;
  int proximaCidade =
      buscarMenorCaminho(list[0].first, cidades, qntd, &distCandidata);

  for (i = 1; i < qntd; i++) {
    int atual = cidades[i];
    int cidadeCandidata =
        buscarMenorCaminho(list[atual].first, cidades, qntd, &distCandidata);

    if (cidadeCandidata < proximaCidade) {
      proximaCidade = cidadeCandidata;
      *distPercorrida = distCandidata;
    }
  }
  printf("Cidade: %d", proximaCidade);
  return proximaCidade;
}

/*------------------------------------------------------------*/
int primAlgoritmo(List *list, int *menorCaminho) {
  escolherCidadeInicial(list, menorCaminho);
  int cidsPercorridas = 1;
  int distanciaPercorrida, distanciaTotal = 0;

  for (; cidsPercorridas < lines; cidsPercorridas++) {
    printf("Entrou\n");
    int cidade = buscarCidadeProxima(list, menorCaminho, cidsPercorridas,
                                     &distanciaPercorrida);
    menorCaminho[cidsPercorridas] = cidade;
    distanciaTotal += distanciaPercorrida;
  }
  return distanciaTotal;
}
