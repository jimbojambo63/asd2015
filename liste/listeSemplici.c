#include <stdio.h>
#include <stdlib.h>
#include "stringa.c"

typedef struct elem{
	int info;
	struct elem *next;
}elist;

typedef elist *plist;

int lungLista(plist p){
    int cont=0;
    while(p!=NULL){
        cont++;
        p=p->next;
    }
    return cont;
}

void inserisciInTesta(plist *p, int n){
    plist temp=(plist)malloc(sizeof(elist));
    temp->info=n;
    temp->next=*p;
    *p=temp;
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

void inserisciInPos(plist *p, int pos, int n){
    int lung;
    int cont=1;
    plist prev,cur,temp;
    temp=(plist)malloc(sizeof(plist));
    temp->info=n;
    lung=lungLista(*p);
    if(lung<pos){
        inserisciInCoda(p,n);
    }else{
        switch (pos){
            case 0:
                printf("errore. inserire posizione maggiore di zero\n");
                break;
            case 1:
                inserisciInTesta(p,n);
                break;
            default:
                prev=*p;
                cur=prev->next;
                while(cont<pos-1){
                    prev=cur;
                    cur=cur->next;
                    cont++;
                }
                prev->next=temp;
                temp->next=cur;
                break;
        }
    }
}

void cancellaInTesta(plist *p){
    printf("cancella in testa\n");
    if(*p!=NULL){
        plist temp;
        temp=*p;
        *p=temp->next;
        free(temp);
    }else{
        printf("lista vuota\n");
    }
}

void cancellaInCoda(plist *p){
    printf("cancella in coda\n");
    plist temp;
    int cont=1;
    int dim;
    dim=lungLista(*p);
    printf("dim = %d\n",dim);
    switch(dim){
        case 0:     printf("lista vuota\n");
                    break;
        case 1:     *p=NULL;
                    free(*p);
                    break;
        default:    
                    temp=*p;
                    while(cont<dim-1){
                        temp=temp->next;
                        cont++;
                    }
                    temp->next=NULL;
    }
}

void cancellaInPos(plist *p,int pos){
    printf("cancella in pos\n");
    plist prev,cur,temp;
    int cont=1;
    int dim;
    dim=lungLista(*p);
    printf("dim = %d\n",dim);
    if(pos>=dim){
        cancellaInCoda(p);
    }
    switch(pos){
        case 0:     printf("Posizione non valida\n");
                    break;
        case 1:     cancellaInTesta(p);
                    break;
        default:    prev=*p;
                    while(cont<pos-1){
                        prev=prev->next;
                        cont++;
                    }
                    temp=prev->next;
                    cur=temp->next;
                    prev->next=cur;
                    free(temp);
    } 
}

int cerca(plist *p, int n){
    plist temp;
    int trovato=0;
    if(*p!=NULL){
        temp=*p;
        while(temp!=NULL && !trovato){
            if(temp->info==n)
                trovato=1;
            else
                temp=temp->next;
        }
    }else{
        return trovato;
    }
}

int contVal(plist *p,int x){
    int cont=0;
    while(*p){
        if((*p)->info==x)
            cont++;
        *p=(*p)->next;
    }
    return cont;
}

void stampaLista(plist p){
    printf("*****************************\n");
    printf("Lista elementi\n");
    if(p==NULL)
        printf("Lista vuota");
    else{
        while(p!=NULL){
            printf("%d",p->info);
            p=p->next;
        }
    }    
    printf("\n*****************************\n");
}

main(){
	plist p;
	p=(plist)malloc(sizeof(plist));
	p=NULL;
	inserisciInTesta(&p,3);
	inserisciInTesta(&p,2);
	inserisciInTesta(&p,3);
	inserisciInCoda(&p,4);
    inserisciInTesta(&p,3);
    inserisciInPos(&p,3,4);
    stampaLista(p);
    // cancellaInTesta(&p);
    // stampaLista(p);
    // cancellaInCoda(&p);
    // stampaLista(p);
    // cancellaInCoda(&p);
    // stampaLista(p);
    // cancellaInCoda(&p);
    // stampaLista(p);
    // cancellaInCoda(&p);
    // stampaLista(p);

    // cancellaInCoda(&p);
    // stampaLista(p);
    // cancellaInCoda(&p);
    // stampaLista(p);

    // inserisciInTesta(&p,8);
    // stampaLista(p);
    // cancellaInTesta(&p);
    // stampaLista(p);
    // cancellaInTesta(&p);
    // stampaLista(p);
    cancellaInPos(&p,1);
    stampaLista(p);
    int x=3;
    printf("il valore %d compare %d volte\n",x,contVal(&p,x));
    if(cerca(&p,2))
        printf("trovato\n");
    else
        printf("non trovato\n");
    int ret;
    ret=lungLista(p);
    free(p);
    printf("lunghezza della lista: %d\n",ret);
}
