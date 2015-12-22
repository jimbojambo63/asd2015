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
int pow2(int base, int esp){
	if(esp==0) return 1;
	int i;
	for(i=1;esp>0;esp--) i=i*base;
	return i;
}


int conta_nodi_lvl(albero T, int lvl){
	if(lvl==0){
		if(T!=NULL)
			return 1;
		else return 0;
	}
	return conta_nodi_lvl(T->dx,lvl-1)+conta_nodi_lvl(T->sx,lvl-1);
}

int altezza(albero T,int lvl){
	if(T!=NULL){ 
		int des,sin;
		des=altezza(T->dx,lvl+1);
		sin=altezza(T->sx,lvl+1);
		if(des>sin) return des;
			return sin;
	}
	return lvl-1;
}

/* INIZIO FUNZIONE */

int albero_completo(albero T){
    
	    /* Dato un un albero binario T di interi, la funzione albero_completo deve ritornare un booleano: 1 se l'albero T è completo, 0 altrimenti. Un albero binario completo di altezza k è un albero binario in cui tutti i nodi, tranne le foglie, hanno esattamente due figli, e tutte le foglie si trovano al livello k. Se l'albero T è vuoto la funzione deve ritornare 0.*/
	if(T!=NULL){
		int h=altezza(T,0);
		if(conta_nodi_lvl(T,h)==pow2(2,h)) return 1;
	}
	return 0;
}
