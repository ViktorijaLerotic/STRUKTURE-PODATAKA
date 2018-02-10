#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define maxB 60
//pazit ne mjenjat fprintf i fscanf!!!
//mjerenje redova!!!
//sve varijable inicijalizirat na pocetnu vrijednost!!!
//nikad ne slati funkciji FILE*
//sve dinamicki alocirati i isprazniti ako treba

//maksimalan broj bodova na kolokviju je 100
typedef struct{
	char imeStudenta[20];
	char prezimeStudrenta[20];
	int brojBodova;
}_student;

int brojacRedova(char*);
int upisStudenta(char*, int, _student*);
void ispisPodataka(_student*, int, int);

int main(){
	
	int maxBrBodova = 0;
	int brRedova=0;
	brRedova = brojacRedova("studenti.txt");	
	_student* stud;
	//dinamicki alocirati memoriju za struct student
	stud = (_student*)malloc(sizeof(_student)*brRedova);
	maxBrBodova = upisStudenta("studenti.txt",brRedova, stud);
	ispisPodataka(stud, brRedova, maxBrBodova);
	
	return 0;
}

int brojacRedova(char* imeDatoteke){
	
	//1)otvoriti datoteku iz koje iscitavam podatke
	FILE* f;
	f = fopen(imeDatoteke, "r");
	if(f==NULL) return -1;
	char* str;
	int brojac=0;
	
	//dok ne dodjem do kraja file-a->univerzalno sa fetgetsom i dinamickom alokacijom memorije
	while(!feof(f)){ 
	
	//zauziman memoriju za pojedini red jer ne moraju svi redovi imati isti br znakova
	str=(char*)malloc(sizeof(char)*maxB);
	
	//iscitavam svaki red i prvjeravam jel duzi od 0(da nije prazan)
	fgets(str, maxB, f);
	if(strlen(str)>0)
	brojac++;
	
	//cistim memoriju za drugi red
	free(str);
		
	}
	fclose(f);
	
return brojac;
}

int upisStudenta(char* imeDatoteke, int br, _student* stud){
	
	//1)otvoriti datoteku iz koje iscitavam podatke
	FILE* f;
	int i;
	int maxBr=0;
	f = fopen(imeDatoteke, "r");
	if(f==NULL) return -1;
	

	
	for(i=0; i<br; i++){
	fscanf(f,"%s %s %d", stud[i].imeStudenta, stud[i].prezimeStudrenta, &stud[i].brojBodova);
	if(stud[i].brojBodova>maxBr)
		maxBr=stud[i].brojBodova;
	}
	rewind(f);
	fclose(f);
	
	return maxBr;
}

void ispisPodataka(_student* stud, int brR, int brB){
	int i;
	printf("Ime\tPrezime\Apsolutno\tRelativno\n");
	for(i=0; i<brR; i++)
	printf("%s\t%s\t%d%%\t%.2f%%\n", stud[i].imeStudenta,stud[i].prezimeStudrenta, stud[i].brojBodova,(float)stud[i].brojBodova/brB*100);
	
}
