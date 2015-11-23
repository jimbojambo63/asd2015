#include <stdio.h>

//Ritorna il carattere ad occorrenza massima in una stringa di LENGTH caratteri
//con complessità 2V+n tale che V=numero di lettere nel vocabolario da 'a' a 'z'; e n la lunghezza della stringa
//Funziona solo per caratteri con codifica ASCII contigua 

#define LENGTH=100

int ind_max(int* V){
	int max,i;
	max=0;
	for(i=0;i<26;i++){
		if(V[max]<V[i])	max=i;
	}
	return max+97;
}

char occ_max(char* str){
	int V[26];
	int i;
	for(i=0;i<26;i++){
		V[i]=0;
	}
	for(i=0;str[i]!='\0';i++){
		V[str[i]-97]++;
	}
	return ind_max(V);
}

int main(){
	char str[LENGTH];
	printf("%s\n","Inserisci una stringa, e ottieni il carattere con più occorrenze");
	scanf("%s",str);
	printf("%s\n",str);
	char *boh=str;
	printf("%c\n",occ_max(str));

}
