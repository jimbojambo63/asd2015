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
	printf("stampa normale: ");
	if(temp==NULL)
		printf("lista vuota\n");
	else{
		while(temp){
			printf("%d",temp->info);
			temp=temp->next;
		}
		printf("\n");
	}
	
	printf("*************************************\n");
}

void stampaReverse(plist temp){
	printf("stampa reverse: ");
	if(temp==NULL)
		printf("lista vuota\n");
	else{	
		while(temp->next){
			temp=temp->next;
		}
		while(temp!=NULL){
			printf("%d",temp->info);
			temp=temp->prev;
		}
	}
	printf("\n*************************************\n");
}

//******************LUNGHEZZA LISTA********************
int lunghezzaLista(plist temp){
	int cont=0;
	if(temp==NULL)
		return 0;
	else{
		while(temp){
			cont++;
			temp=temp->next;
		}
	}
	return cont;
}

//**********************RICERCA************************
//ritorna 0 se non trovato, altrimenti ritorna la posizione
int cerca(plist temp, int val){
	// plist temp;
	// temp=*p;
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
	printf("inserisci il valore %d in testa\n",n);
    plist temp=(plist)malloc(sizeof(elist));
    temp->info=n;
    temp->prev=NULL;
    if(*p == NULL) {
        *p = temp;
    }else{
  //   	plist succ=temp->next;
		// *p=succ;
		// succ->prev=NULL;

    	temp->next=*p;
    	(*p)->prev=temp;
    	*p=temp;    	
    }
}

void inserisciInCoda(plist *p, int n){
	printf("inserisci il valore %d in coda\n",n);
    plist temp=(plist)malloc(sizeof(elist));
    temp->info=n;
    temp->next=NULL;
    plist temp2;
    if(*p==NULL)
    	*p=temp;
    else{
        temp2=*p;
        while(temp2->next!=NULL){
            temp2=temp2->next;
        }
        temp2->next=temp;
        temp->prev=temp2;
    }
}

void inserisciInPos(plist *p, int val, int pos){
	printf("inserisci il valore %d in posizione %d\n",val,pos);
	plist temp,corr,prec;
    temp=(plist)malloc(sizeof(plist));
	temp->info=val;
	int cont=2;
	int dim=lunghezzaLista(*p);
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

//********************CREA LISTA***********************
plist creaLista(int dim){
	plist lista=(plist)malloc(sizeof(elist));
	lista=NULL;
	int i;
	for(i=0;i<dim;i++){
		int n=rand()%9+1;
		inserisciInCoda(&lista,n);
	}
	return lista;
}

//*******************CANCELLAZIONE*********************
void cancellaInTesta(plist *p){
	printf("cancella in testa\n");
	plist temp=*p;
	if(temp==NULL)
		printf("Errore: lista vuota\n");
	else{
		*p=temp->next;
		free(temp);
	}
}

void cancellaInCoda(plist *p){
	printf("cancella in coda\n");
	plist temp=*p;
	plist prec=NULL;
	int dim=lunghezzaLista(*p);
	printf("dim prima = %d\n",dim);
	switch(dim){
		case 0:		printf("Errore: lista vuota\n");
					break;
		case 1:		*p=NULL;
                    free(*p);
					break;
		default:	
					while(temp){
						prec=temp->prev;
						temp=temp->next;
					}
					prec->next=NULL;
					free(temp);
					break;
	}
	dim=lunghezzaLista(*p);
	printf("dim dopo = %d\n",dim);
}

void cancellaInPos(plist *p, int pos){
	printf("cancella in pos %d\n",pos);
	if(*p==NULL)
		printf("Errore: lista vuota\n");
	else{
		int dim=lunghezzaLista(*p);
		if(pos>dim||pos==0){
			printf("Errore: posizione non valida\n");
		}else if(pos==1){
			cancellaInTesta(p);
		}else if(pos==dim){
			cancellaInCoda(p);
		}else{
			int cont=1;
			plist temp=*p;
			plist prec=NULL;
				//plist succ=NULL;
			while(cont<pos){
				prec=temp;
				temp=temp->next;
				cont++;
				}
			printf("prec : %d\n",prec->info);
			//succ=temp->next;
			printf("temp : %d\n",temp->info);
			//printf("succ : %d\n",succ->info);
			temp->next->prev=prec;
			prec->next=temp->next;
			free(temp);
		}
	}
}

void cancellaVal(plist *p, int val){
	printf("cancella val %d\n",val);
	if(*p==NULL)
		printf("Errore: lista vuota\n");
	else{
		int cont=1;
		plist temp=*p;
		int dim=lunghezzaLista(*p);
		while(cont<dim){
			if(val==temp->info){
				if(cont==1||temp->prev==NULL){
					plist succ=temp->next;
					*p=succ;
					succ->prev=NULL;
					printf("valore %d cancellato in pos %d\n",val,cont);
					//free(temp);
				}else{
					plist prec=temp->prev;
					plist succ=temp->next;
					prec->next=succ;
					succ->prev=prec;
					//free(temp);
				}
			}
			temp=temp->next;
			cont++;
		}
		if(cont==dim){
			if(val==temp->info)
				cancellaInCoda(p);
		}
	}	
}

//*******************INTERSEZIONE**********************
void intersezione(plist lista1, plist lista2){
	plist lista=(plist)malloc(sizeof(elist));
	plist list1=lista1;
	lista=NULL;
	while(lista1){
		plist lis2=lista2;		
		while(lis2){
			// printf("confronto %d e %d\n",lista1->info,lis2->info);
			if(lista1->info==lis2->info){
				int pos=cerca(lista,lista1->info);
				if(pos==0)
					inserisciInCoda(&lista,lista1->info);
			}
			lis2=lis2->next;
		}
		lista1=lista1->next;
	}
	printf("*************************************\nl'intersezione tra la lista\n");
	stampaNormale(list1);
	printf("e la lista\n");
	stampaNormale(lista2);
	printf("è uguale a\n");
	stampaNormale(lista);
}

//**********************UNIONE*************************
void unione(plist lista1, plist lista2){
	plist lista=(plist)malloc(sizeof(elist));
	plist list1=lista1;
	lista=NULL;
	while(lista1){
		plist lis2=lista2;		
		while(lis2){
			//printf("confronto %d e %d\n",lista1->info,lis2->info);	
			int pos=cerca(lista,lis2->info);
			if(pos==0)
				inserisciInCoda(&lista,lis2->info);
			lis2=lis2->next;
		}
		int pos=cerca(lista,lista1->info);
			if(pos==0)
				inserisciInCoda(&lista,lista1->info);
		lista1=lista1->next;
	}
	printf("*************************************\nl'unione tra la lista\n");
	stampaNormale(list1);
	printf("e la lista\n");
	stampaNormale(lista2);
	printf("è uguale a\n");
	stampaNormale(lista);
}

//*************************MAIN************************
int main(){

	//******CREAZIONE LISTA*******
	plist lista=NULL;
	inserisciInCoda(&lista,3);
	inserisciInCoda(&lista,5);
	inserisciInTesta(&lista,6);
	inserisciInTesta(&lista,2);

	stampaNormale(lista);
	stampaReverse(lista);
	printf("lunghezza lista = %d\n",lunghezzaLista(lista));

	//********RICERCA********
	int pos;
	int val=6;
	pos=cerca(lista,val);
	if(pos==0)
		printf("valore %d non trovato\n",val);
	else
		printf("valore %d trovato in posizione = %d\n",val,pos);
	stampaNormale(lista);

	//********INSERISCI IN POSIZIONE DATA*********
	inserisciInPos(&lista,7,4);
	stampaNormale(lista);
	stampaReverse(lista);
	printf("lunghezza lista = %d\n",lunghezzaLista(lista));
	free(lista);

	//*******INSERIMENTO E CANCELLAZIONE NUOVA LISTA**********
	printf("*************************************\n");
	plist l1=NULL;
	inserisciInCoda(&l1,5);
	inserisciInTesta(&l1,7);
	inserisciInTesta(&l1,3);
	stampaNormale(l1);
	//stampaReverse(l1);
	cancellaInCoda(&l1);
	// cancellaInTesta(&l1);
	//stampaNormale(l1);
	cancellaInCoda(&l1);
	stampaNormale(l1);
	plist l2=NULL;
	inserisciInCoda(&l2,7);
	inserisciInCoda(&l2,3);
	inserisciInCoda(&l2,7);
	inserisciInCoda(&l2,7);
	inserisciInCoda(&l2,5);
	inserisciInCoda(&l2,7);
	stampaNormale(l2);
	cancellaInPos(&l2,2);
	stampaNormale(l2);
	stampaReverse(l2);
	cancellaInPos(&l2,8);
	stampaNormale(l2);
	stampaReverse(l2);
	cancellaVal(&l2,7);
	stampaNormale(l2);
	stampaReverse(l2);
	cancellaVal(&l2,5);
	stampaNormale(l2);
	stampaReverse(l2);
	free(l1);
	free(l2);

	//**********INTERSEZIONE ED UNIONE*********
	printf("************INTERSEZIONE*************\n");
	printf("*************************************\n");
	plist lis1=(plist)malloc(sizeof(elist));
	plist lis2=(plist)malloc(sizeof(elist));
	srand(time(NULL));
	printf("Lista 1\n");
	lis1=creaLista(4);
	stampaNormale(lis1);
	printf("Lista 2\n");
	lis2=creaLista(6);
	stampaNormale(lis2);
	intersezione(lis1,lis2);
	printf("***************UNIONE****************\n");
	printf("*************************************\n");
	unione(lis1,lis2);
	return 0;
}
