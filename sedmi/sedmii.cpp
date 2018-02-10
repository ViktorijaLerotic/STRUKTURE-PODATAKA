

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
typedef struct node* position;
typedef struct stack* positionS;

struct stack{
	int ele;
	positionS next;
}_STACK;
struct node{
	char* element;
	position left;
	position right;
}_NODE;


void push(positionS head, int element);
int pop(positionS head);
void ReadFromFile(char* fileName, positionS result);
void ExecuteOpr(int x,int y,char* q, positionS head);
int main(void){
	
	positionS head = (positionS)malloc(sizeof(_STACK));
	head->ele = NULL;
	head->next = NULL;
	
	ReadFromFile("postfix.txt", head);
int f = pop(head);
puts(" ");
	printf("%d", f);
	
	return 0;
}


void push(positionS head, int element){
	positionS n= (positionS)malloc(sizeof(_STACK));
	n->ele = element;
	n->next = NULL;
	n->next = head->next;
	head->next = n;
}
int pop(positionS head){
	
	positionS q = head->next;
	positionS p = q->next;
	int a;
	head->next = p;
	
	a = q->ele;
	return a;	

	free(q);
	
}
void ExecuteOpr(int x,int y,char* q, positionS head){

	switch(*q){
		case '+':
				push(head, x + y);
				break;
				
		case '-':
				
				push(head, x - y);
				break;
			
		case '*':
				push(head, x * y);
				break;
			
		case '/':
				push(head, x / y);
				break;
			
	}
	
}

void ReadFromFile(char* fileName, positionS result){
	
	int value;
	FILE* f;
	
	f = fopen(fileName, "r");
	if(f == NULL) printf("Datoteka nije dobro ucitana!\n");
	
	while(!feof(f)){
		int x = 0, y = 0;
		
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
					push(result, atoi(q->element));
			else{
				y = pop(result);
				x = pop(result);
				printf("%d  %d %s  ",x, y, q->element);
				ExecuteOpr(x,y,q->element, result);
				
				}
			}	
		}
	fclose(f);
	}



