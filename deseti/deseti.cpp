//Napisati program koji iz datoteke èita postfiks izraz i zatim stvara stablo proraèuna. Iz
//gotovog stabla proraèuna upisati u datoteku infiks izraz.

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
typedef struct node* position;
typedef struct stack* positionS;

struct stack{
	position ele;
	positionS next;
}_STACK;
struct node{
	char* element;
	position left;
	position right;
}_NODE;

void PrintInfix(position head);
void push(positionS head, position element);
position pop(positionS head);
void ReadFromFile(char* fileName, positionS result);
	
int main(void){
	
	positionS head = (positionS)malloc(sizeof(_STACK));
	head->ele = NULL;
	head->next = NULL;
	
	ReadFromFile("postfix.txt", head);
	// ISPIS INORDER- PRVO SVE SA LIJEVE STRANE, PA GLAVNI CVOR, PA SVE SA DESNE STRANE!!!
	// OBICAN ISPIS
	
	position root = pop(head);
	PrintInfix(root->left);
	printf("%s ", root->element);
	PrintInfix(root->right);
	


	
	return 0;
}
//PUSH -> NA JEDNU STRUKTURU(STACK) STAVLJAM DRUGU STRUKUTUR
//TAKO DA ALOCIRA JEDAN CVOR STRUKUTRE STACK  I UBACIM U NJEGA STRUKTURU NODE
// A ONDA IZVRSIM ONAJ INSERT
void push(positionS head, position element){
	
	positionS q = (positionS)malloc(sizeof(_STACK));
	
	if(q != NULL)
	{
		q->ele = element;
		q->next = head->next;
		head->next = q;
	}
}
position pop(positionS head){
	
	positionS q = head->next;
	positionS p = q->next;
	position a;
	head->next = p;
	
	a = (position)malloc(sizeof(_NODE));
	a = q->ele;
	return a;	

	free(q);
	
}

void ReadFromFile(char* fileName, positionS result){
	
	int value;
	FILE* f;
	
	f = fopen(fileName, "r");
	if(f == NULL) printf("Datoteka nije dobro ucitana!\n");
	
	while(!feof(f)){
		
		position q = (position)malloc(sizeof(_NODE));
		if(q){
			//OBAVEZNO ALOCIRAT MEMORIJU ZA CVOR I SVIM CLANOVIMA STRUKUTRE PRIDRUZIT POCETNE VRIJEDNOSTI(NULL,...)
			q->element = (char*)malloc(sizeof(char)*25);
			q->element[24] = '\0';
			fscanf(f, " %s", q->element, 24);
			q->left = NULL;
			q->right = NULL;
			
			//provjeravam je li to sto je u cvoru znamenka ili neka operacija te ovisno o tome radim sto je potrebno
			if(atoi(q->element))
					push(result, q);
			else{
				q->right = pop(result);
				q->left = pop(result);
				push(result, q);
				}
			}	
		}
	fclose(f);
	}


void PrintInfix(position N)
{
	if(N != NULL)
	{
		if(atoi(N->element) || isalpha(N->element[0]))
			;
		else
			printf("(");
		PrintInfix(N->left);
		printf(" %s ", N->element);
		PrintInfix(N->right);
		if(atoi(N->element) || isalpha(N->element[0]))
			;
		else
			printf(")");
	}
}

