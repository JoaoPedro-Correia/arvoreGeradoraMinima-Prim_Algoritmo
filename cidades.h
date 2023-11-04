#ifndef CIDADES_H
#define CIDADES_H
#include <stdio.h>
void printCidade(int cidade);

enum cidades_conectadas {
  Oradea = 1,
  Zerind,
  Arad,
  Timisoara,
  Lugoj,
  Meehadia,
  Drobeta,
  Sibiu,
  Rimnicu_Vilcea,
  Craiova,
  Fagaras,
  Pitesti,
  Bucharest,
  Giurgiu,
  Neamt,
  Iasi,
  Vaslui,
  Urziceni,
  Hirsova,
  Eforie
};

/*------------------------------------------------------------*/
void printCidade(int cidade) {
  if (cidade >= Oradea && cidade <= Eforie) {
    switch (cidade) {
    case Oradea:
      printf("Oradea");
      break;
    case Zerind:
      printf("Zerind");
      break;
    case Arad:
      printf("Arad");
      break;
    case Timisoara:
      printf("Timisoara");
      break;
    case Lugoj:
      printf("Lugoj");
      break;
    case Meehadia:
      printf("Meehadia");
      break;
    case Drobeta:
      printf("Drobeta");
      break;
    case Sibiu:
      printf("Sibiu");
      break;
    case Rimnicu_Vilcea:
      printf("Rimnicu_Vilcea");
      break;
    case Craiova:
      printf("Craiova");
      break;
    case Fagaras:
      printf("Fagaras");
      break;
    case Pitesti:
      printf("Pitesti");
      break;
    case Bucharest:
      printf("Bucharest");
      break;
    case Giurgiu:
      printf("Giurgiu");
      break;
    case Neamt:
      printf("Neamt");
      break;
    case Iasi:
      printf("Iasi");
      break;
    case Vaslui:
      printf("Vaslui");
      break;
    case Urziceni:
      printf("Urziceni");
      break;
    case Hirsova:
      printf("Hirsova");
      break;
    case Eforie:
      printf("Eforie");
      break;
    }
  }
}
#endif
