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
    memset(visto, 0, sizeof(visto)) ;
    for (int j = 0 ; j < 9 ; j++) {
      int num = n -> sudo[i][j] ;
      if (num == 0) continue;
      if (visto[num]) return 0 ;
      visto[num] = 1 ;
    }
  }

  for (int j = 0 ; j < 9 ; j++) {
    memset(visto, 0, sizeof(visto)) ;
    for (int i = 0 ; i < 9 ; i++) {
      int num = n -> sudo[i][j] ;
      if (num == 0) continue;
      if (visto[num]) return 0 ;
      visto[num] = 1 ;
    }
  }

  for (int k = 0 ; k < 9 ; k++) {
    memset(visto, 0, sizeof(visto)) ;
    for (int p = 0 ; p < 9 ; p++) {
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
    List* list=createList();
    
    int fila, col ;
    bool encontrado = false ;

    for (int i = 0 ; i < 9 && !encontrado ; i++) {
      for (int j = 0 ; j < 9 ; j++) {
        if (n -> sudo[i][j] == 0) {
          fila = i ;
          col = j ;
          encontrado = true ;
          break ;
        }
      }
    }

    if (!encontrado) return list ;

    for (int num = 1 ; num <= 9 ; num++) {
      Node *newNode = copy(n) ;
      newNode -> sudo[fila][col] = num ;
      pushBack(list, newNode) ;
    }


    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}


int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}