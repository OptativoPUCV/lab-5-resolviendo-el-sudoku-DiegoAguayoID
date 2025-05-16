#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"


typedef struct{
  int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
        for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
        }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
        printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int visto[10] ;

  for (int i = 0 ; i < 9 ; i++) {
    memset(visto, 0, sizeof(visto)) ; // Limpio el arreglo  para las filas
    for (int j = 0 ; j < 9 ; j++) {
      int num = n -> sudo[i][j] ; // Tomo el numero en fila i columna j
      if (num == 0) continue; // Ignoro los 0 
      if (visto[num]) return 0 ; // Si ya aparecio el numero ( == 1) retorno 0 
      visto[num] = 1 ; // Marcar que ese numero ya está
    }
  }

  for (int j = 0 ; j < 9 ; j++) {
    memset(visto, 0, sizeof(visto)) ; // Limpio el arreglo  para las columnas
    for (int i = 0 ; i < 9 ; i++) {
      int num = n -> sudo[i][j] ; // Se invierte el orden de i y j
      if (num == 0) continue;
      if (visto[num]) return 0 ;
      visto[num] = 1 ;
    }
  }

  for (int k = 0 ; k < 9 ; k++) {
    memset(visto, 0, sizeof(visto)) ; // Reinicio el arreglo
    for (int p = 0 ; p < 9 ; p++) { // VERIFICO EL 3X3 con el ejemplo dado en el readme
      int i = 3 * (k / 3) + (p / 3) ;
      int j = 3 * (k % 3) + (p % 3) ;
      int num = n -> sudo[i][j] ;
      if (num == 0) continue;
      if (visto[num]) return 0 ;
      visto[num] = 1 ;
    }
  }

  return 1 ;
}


List* get_adj_nodes(Node* n){
    List* list=createList(); // Creo lista de nodos
    
    int fila, col ; // Defino variable fila y col, para guardar la posicion
    bool encontrado = false ; // Parte en falso el encontrado

    for (int i = 0 ; i < 9 && !encontrado ; i++) {
      for (int j = 0 ; j < 9 ; j++) {
        if (n -> sudo[i][j] == 0) { //Busco en todo el nodo si hay algun 0
          fila = i ;
          col = j ; 
          encontrado = true ; // Copio su posicion y encontrado pasa a ser True
          break ;
        }
      }
    }

    if (!encontrado) return list ;

    for (int num = 1 ; num <= 9 ; num++) {
      Node *newNode = copy(n) ; // Copio el nodo original
      newNode -> sudo[fila][col] = num ; // Coloco el numero en la fila y columna que tiene 0
      if (is_valid(newNode)) pushBack(list, newNode) ; // Si el nodo es valido lo agrego
      else free(newNode) ;
    }


    return list;
}


int is_final(Node* n){
    for (int i = 0 ; i < 9 ; i++) {
      for (int j = 0 ; j < 9 ; j++) {
        if (n -> sudo[i][j] == 0) return 0 ; //No esta completo si esta una casilla vacia
      }
    }

    return 1 ; // Todo esta completo
}

Node* DFS(Node* n, int* cont){
  Stack* S = createStack() ;
  push(S, n) ;
  *cont = 0 ;

  while (!is_empty(S)) {
    Node *current = top(S) ;
    pop(S) ;
    (*cont) ++ ;

    if (is_final(current)) return current ;

    List* adj = get_adj_nodes(current) ;

    Node *adjNode = frist(adj) ;
    while (adjNode != NULL) {
      push(S, adjNode) ;
      adjNode = next(adj) ;
    }

    free(current) ;
  }

  return NULL ;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}
*/