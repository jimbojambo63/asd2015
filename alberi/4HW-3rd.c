#include <stdio.h>  /* ora puoi usare NULL */

/* scrivi qui la definizione del tipo nodo_albero che rappresenta una struttura con tre campi: primo campo ha nome info ed è di tipo intero, secondo campo ha nome sx (un puntatore al sottoalbero sinistro), terzo campo ha nome dx (un puntatore al sottoalbero destro) */
typedef struct nodo{
  int info;
  struct nodo* sx;
  struct nodo* dx;
}nodo_albero;



/* scrivi qui la definizione del tipo albero che rappresenta un puntatore alla struttura nodo_albero */
typedef nodo_albero* albero;



/* scrivi qui eventuali funzioni di appoggio */
int conta_nodi_lvl(albero T, int lvl){
  if(lvl==0 && T) return 1;
  if(T) return conta_nodi_lvl(T->dx,lvl-1)+conta_nodi_lvl(T->sx,lvl-1);
  return 0;
}


/* INIZIO FUNZIONE */

int larghezza_albero(albero T){
    
    /* Dato un un albero binario T di interi, la funzione larghezza_albero deve ritornare la larghezza di T; la larghezza di un albero binario è il numero massimo di nodi che stanno tutti al medesimo livello. Nel caso in cui T sia vuoto la funzione ritornerà 0.*/

  int lvl=0;
  int max=0;
  if(T){
    int nodi=1;
    for(;nodi!=0;lvl++){
      nodi=conta_nodi_lvl(T,lvl);
      if(nodi>max) max=nodi;
    }
  }
  return max;   
}
