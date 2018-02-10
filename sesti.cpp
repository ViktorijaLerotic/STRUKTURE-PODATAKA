#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
typedef struct node* position;
struct node{
	int data;
	position next;
	
}_NODE;
position CreateHeadNode();
position CreateNode(int);
void Insert(position, position);
void AddAtBeginning(position, position);
void AddAtTheEnd(position, position);
int GenerateRandomNumbers(int, int);
void DeleteFirstElement(position);
void PrintElements(position);
void push_stack(position);
void push_q(position);
void pop(position);
int main(){
	
	position head = CreateHeadNode();
	
	push_stack(head);
	push_stack(head);
	pop(head);

	
	free(head);
	
	return 0;
}

position CreateHeadNode(){
	position head = (position)malloc(sizeof(_NODE));
	if(head == NULL) return NULL;
	head->next = NULL;

	return head;
}

position CreateNode(int x){
	position q = (position)malloc(sizeof(_NODE));
	q->data = x;
	q->next = NULL;

return q;	
}
void Insert(position Prev, position Next){
	Next->next = Prev->next;
	Prev->next = Next;
}
void AddAtBeginning(position head, position element){
	Insert(head, element);
}
void AddAtTheEnd(position head, position element){
	position last = head;
	while(last->next != NULL){
		last = last->next;
	}
	
	Insert(last, element);
}
int GenerateRandomNumbers(int lower, int upper){
	return rand()%(upper - lower +1) + lower;
}
void DeleteFirstElement(position head){
	position first = head->next;
	head->next = first->next;
	free(first);
}
void PrintElements(position head){
	position element = head->next;
	while(element != NULL){
		printf("%d\n", element->data);
		element=element->next;
	}
}
void push_stack(position head){
	AddAtBeginning(head,CreateNode(GenerateRandomNumbers(10,100)));
	PrintElements(head);
}
void push_q(position head){
	AddAtTheEnd(head,CreateNode(GenerateRandomNumbers(10,100)));
	PrintElements(head);
}
void pop(position head){

	while(head->next!= NULL)
		DeleteFirstElement(head);
		
	printf("Nakon brisanja: ");
	PrintElements(head);	
}
