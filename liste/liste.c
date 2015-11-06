#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int info;
	struct nodo* next;
	struct nodo* prev;
}nlist;

typedef nlist* plist;

void insert_head(plist* list, int info){
	plist primo=*list;
	plist tmp=(plist) malloc(sizeof(nlist));
	tmp->info=info;
	tmp->next=*list;
	if(primo!=NULL)		primo->prev=tmp;
	*list=tmp;
}

void insert_tail(plist* list, int info){
	plist tmp=(plist)malloc(sizeof(nlist));
	tmp->info=info;
	plist index=*list;
	if(index!=NULL){
		while(index->next!=NULL){
			index=index->next;
		}
		tmp->next=NULL;
		tmp->prev=index;
		index->next=tmp;
	}
	else	*list=tmp;
}

/*inserisce un nodo nella posizione pos a partire da 0, in casi di overflow
il nodo viene inserito in ultima posizione, ritorna il numero della posizione
in cui è stato inserito il nuovo nodo*/
int insert(plist* list, int info, int pos){
	plist tmp=(plist)malloc(sizeof(nlist));
	plist cur_pos=*list;
	int i;
	tmp->info=info;
	for(i=0; i<pos && cur_pos!=NULL; i++){
		cur_pos=cur_pos->next;
	}
	tmp->next=cur_pos;
	tmp->prev=cur_pos->prev;
	if(i!=0){
		cur_pos->prev->next=tmp;
	}
	cur_pos->prev=tmp;
	return i;
}

void delete_head(plist* list){
	if(*list!=NULL){
		plist head=*list;
		*list=head->next;
		head->prev=NULL;
		free(head);
	}
}

void delete_tail(plist* list){
	if(*list!=NULL){
		plist index=*list;
		while(index->next!=NULL){
			index=index->next;
		}
		index->prev->next=NULL;
		free(index);
	}
}

void delete_pos(plist* list, int pos){
	if(*list!=NULL){
		plist cur_pos=*list;
		if(pos==0){
			*list=NULL;
			free(cur_pos);
		}
		else{
			for(; pos>0 && cur_pos!=NULL; pos--){
				cur_pos=cur_pos->next;
			}
			cur_pos->prev->next=cur_pos->next;
			if(cur_pos!=NULL)	cur_pos->next->prev=cur_pos->prev;
			free(cur_pos);
		}
	}
}

/*elimina tutti i nodi da una lista doppiamente concatenata con il campo info==parametro
non funziona se il nodo da eliminare è in testa*/
void delete(plist *list, int info){
	plist cur_pos=*list;
	while(cur_pos!=NULL){
		if(cur_pos->info==info){

			//mi tengo il nodo da liberare
			plist tmp=cur_pos;

			if(cur_pos->next!=NULL)		cur_pos->next->prev=cur_pos->prev;

			//se non è il primo nodo lo "salto" e mi posiziono sul precedente
			if(cur_pos->prev!=NULL){
				cur_pos->prev->next=cur_pos->next;
				cur_pos=cur_pos->prev;
			}

			//se è il primo nodo lo "salto" e mi posiziono sul primo
			else{
				*list=cur_pos->next;
				cur_pos=*list;
			}

			//libero il nodo
			free(tmp);
		}

		//se info non coincide vado avanti
		else	cur_pos=cur_pos->next;
	}
}


int length(plist *list){
	int length=0;
	plist cur=*list;
	for(;cur!=NULL;length++){
		cur=cur->next;
	}
	return length;
}

void print_list(plist *list){
	plist cur=*list;
	while(cur!=NULL){
		printf("%d",cur->info);
		cur=cur->next;
	}
}

main(){
	plist p;
	p=(plist)malloc(sizeof(nlist));
	p=NULL;
	insert_head(&p,3);
	insert_head(&p,2);
	insert_head(&p,5);
	insert_tail(&p,4);
    insert_head(&p,8);

    print_list(&p);
    printf("%s","\n");

    insert(&p,6,3);

    print_list(&p);
    printf("%s","\n");

    delete_head(&p);

    print_list(&p);
    printf("%s","\n");
    
    delete_tail(&p);
    
    print_list(&p);
    printf("%s","\n");
    
    delete_pos(&p,1);
    
    print_list(&p);
    printf("%s","\n");
    printf("%s","eliminare il primo nodo in delete(lista, info) non funziona\n");
	delete(&p,5);
    
    print_list(&p);
    printf("%s","\n");
    
    printf("lunghezza della lista: %d\n",length(&p));
    free(p);
}