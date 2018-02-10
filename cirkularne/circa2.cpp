#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct node* position;
struct node{
	int data;
	position next;
	position prev;
}_NODE;

position CreateHeadNode();
position CreateNode(int);
position GetLastElement(position);
void InsertAtStart(position, int);
void Print(position);
int main(void){
	position head = CreateHeadNode();

	InsertAtStart(head, 3);
//	InsertAtEnd(head, 5);
	InsertAtStart(head, 23);
//	InsertAtEnd(head, 15);
	InsertAtStart(head, 32);
//	InsertAfter(head, 3, 4);
//	InsertBefore(head, 3 , 2);

	Print(head);

	free(head);
	return 0;
}

position CreateHeadNode(){
	position head = (position)malloc(sizeof(_NODE));
	if(head == NULL) return NULL;
	head->next = NULL;
	head->prev = NULL;
	return head;
}

position CreateNode(int x){
	position q = (position)malloc(sizeof(_NODE));
	q->data = x;
	q->next = NULL;
	q->prev = NULL;
return q;	
}
position GetLastElement(position head){
	//p je prvi stvarni element
	position p = head->next;
	//q je element na kojeg zadnji element pokazuje
	position q = head->next;
	
	if(head->next == NULL)
	return NULL;
	
	if(p->next == NULL)
		return p;
	else{	
		while(p->next != q)
		p = p->next;
	return p;
	}
	
}
void AddAtStart(position head, int x){
	position q = CreateNode(x);
	position last = GetLastElement(head);
	if(head->next == NULL)
		head->next = q;
	else{
		q->next = head->next;
		head->next->prev = q;
		head->next = q;
		last->next = q;
	}
}
void Print(position head){
	//prvi stvarni element je p
	position p = head->next;
	//na to pokazuje zadnji element
	position q = head->next;
		
	if(head->next == NULL)
	printf("Lista je prazna");

	else {
		printf("%d\t", p->data);
	while(p->next != q){
			p = p->next;
			printf("%d\t", p->data);
			}
		}
}
