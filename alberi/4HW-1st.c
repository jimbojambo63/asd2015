#include <stdio.h>  /* ora puoi usare NULL */

/* scrivi qui la definizione del tipo nodo_albero che rappresenta una struttura con tre campi: primo campo ha nome info ed è di tipo intero, secondo campo ha nome sx (un puntatore al sottoalbero sinistro), terzo campo ha nome dx (un puntatore al sottoalbero destro) */
typedef struct nodo{
  int info;
  struct nodo* sx;
  struct nodo* dx;
}nodo_albero;



/* scrivi qui la definizione del tipo albero che rappresenta un puntatore alla struttura nodo_albero */
typedef nodo_albero* albero;



/* INIZIO FUNZIONE */

int albero_pieno(albero T){
    
    /* Dato un un albero binario T di interi, la funzione albero_pieno deve ritornare un booleano: 1 se l'albero T è "pieno", 0 altrimenti. Un albero binario “pieno” è un albero binario in cui tutti i nodi hanno esattamente 0 o 2 figli, e nessun nodo ha 1 figlio. Se l'albero T è vuoto la funzione deve ritornare 1.*/

  if(T==NULL) return 1;
  if( (T->dx && T->sx) || ((T->dx==NULL)&&(T->sx==NULL)) )
    return 1 && albero_pieno(T->dx) && albero_pieno(T->sx);
  return 0;    
}
