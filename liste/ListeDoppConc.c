#include <stdio.h>
#include <stdlib.h>

typedef struct elem{
	int info;
	struct elem *next;
	struct elem *prev;
}elist;

typedef elist *plist;

//**************************STAMPE*******************

void stampaNormale(plist temp){
	printf("*******stampa normale*******\n");
	while(temp){
		printf("%d",temp->info);
		temp=temp->next;
	}
	printf("\n****************************\n");
}

void stampaReverse(plist temp){
	printf("*******stampa reverse*******\n");
	while(temp->next!=NULL){
		temp=temp->next;
	}
	while(temp){
		printf("%d",temp->info);
		temp=temp->prev;
	}
	printf("\n****************************\n");
}

//******************LUNGHEZZA LISTA********************
int lunghezzaLista(plist *p){
	plist temp;
	temp=*p;
	int cont=0;
	while(temp){
		cont++;
		temp=temp->next;
	}
	return cont;
}

//**********************RICERCA************************
//ritorna 0 se non trovato, altrimenti ritorna la posizione
int cerca(plist *p, int val){
	plist temp;
	temp=*p;
	int cont=1;
	int pos=0;
	while(temp){
		if(temp->info==val){
			pos=cont;
			return pos;
		}
		temp=temp->next;
		cont++;
	}
	return pos;
}

//********************INSERIMENTO**********************
void inserisciInTesta(plist *p, int n){
    plist temp=(plist)malloc(sizeof(elist));
    temp->info=n;
    if(*p == NULL) {
        *p = temp;
    }else{
    	temp->next=*p;
    	(*p)->prev=temp;
    	*p=temp;    	
    }
}

void inserisciInCoda(plist *p, int n){
    plist temp=(plist)malloc(sizeof(elist));
    temp->info=n;
    temp->next=NULL;
    plist temp2;
    if(*p!=NULL){
        temp2=*p;
        while(temp2->next!=NULL){
            temp2=temp2->next;
        }
        temp2->next=temp;
    }else{
        *p=temp;
    }
}

void inserisciInPos(plist *p, int val, int pos){
	printf("*******INSERISCI IN POSIZIONE*******\n");
	plist temp,corr,prec;
    temp=(plist)malloc(sizeof(plist));
	temp->info=val;
	int cont=2;
	int dim=lunghezzaLista(p);
	printf("lunghezza lista = %d\n",dim);
	if(pos>dim){
		inserisciInCoda(p,val);
	}else{
		switch(pos){
			case 0:		printf("Errore, inserire posizione valida\n");
						break;
			case 1:		inserisciInTesta(p,val);
						break;
			default:	//prec=(plist)malloc(sizeof(plist));
						prec=*p;
						corr=prec->next;
						while(cont<pos){
							cont++;
							prec=corr;
							corr=corr->next;
						}
						prec->next=temp;
						temp->next=corr;
						temp->prev=prec;
						corr->prev=temp;
						break;
		}
	}
	
}

void inserisciPrimaDi(plist *p, int val){

}

//*************************MAIN************************
main(){
	//******CREAZIONE LISTA*******
	plist lista;
	inserisciInTesta(&lista,3);
	inserisciInTesta(&lista,5);
	inserisciInTesta(&lista,6);
	inserisciInTesta(&lista,2);

	stampaNormale(lista);
	stampaReverse(lista);
	printf("lunghezza lista = %d\n",lunghezzaLista(&lista));

	//********RICERCA********
	int pos;
	int val=6;
	pos=cerca(&lista,val);
	if(pos==0)
		printf("Non trovato\n");
	else
		printf("valore %d in posizione = %d\n",val,pos);
	stampaNormale(lista);
	//********INSERISCI IN POSIZIONE DATA*********
	inserisciInPos(&lista,7,4);
	stampaNormale(lista);
	stampaReverse(lista);
}
