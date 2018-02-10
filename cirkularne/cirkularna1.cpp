#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct node* position;
struct node{
	int data;
	position next;
	
}_NODE;
position CreateHeadNode();
position CreateNode(position, int);
position GetLastElement(position);
void InsertAtStart(position, int);
void InsertAtEnd(position, int);
void InsertBefore(position, int, int);
void InsertAfter(position, int, int);
position FindPrev(position, int);
position Find(position, int);
void DeleteTheElement(position, int);
void Print(position);
void DeleteAll(position);
int main(void){
	position head = CreateHeadNode();
	position p = NULL;
	position q = NULL;
	InsertAtStart(head, 3);
	InsertAtEnd(head, 5);
	InsertAtStart(head, 23);
	InsertAtEnd(head, 15);
	InsertAtStart(head, 32);
	InsertAfter(head, 3, 4);
	InsertBefore(head, 3 , 2);

	Print(head);
	/*p = FindPrev(head, 15);
	printf("\nElement koji prethodi broju 15 je %d", p->data);
	q = Find(head, 5);
	printf("\nElement koji trazimo je %d", p->data);*/
	printf("\n");
	DeleteTheElement(head, 15);
	Print(head);
	DeleteAll(head);
	printf("\n");
	Print(head);
	free(head);
	return 0;
}
position CreateHeadNode(){
	position head = (position)malloc(sizeof(_NODE));
	if(head == NULL) return NULL;
	head->next = NULL;

	return head;
}

position CreateNode(position head,int x){
	position q = (position)malloc(sizeof(_NODE));
	q->data = x;
	q->next = NULL;

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
void InsertAtStart(position head, int x){
	position q = CreateNode(head,x);
	position last = GetLastElement(head);
	
	if(head->next == NULL){
		head->next = q;
		q->next = head->next;
	}

	else{	
		q->next = head->next;	
		head->next = q;
		last->next = q;
	}
}
void InsertAtEnd(position head, int x){
	position q = CreateNode(head,x);
	position last = GetLastElement(head);
	
	if(head->next == NULL){
		head->next = q;
		q->next = head->next;
	}
	else{
		q->next = last->next;
		last->next = q;
	}
	
}
position FindPrev(position head, int x){
	position p = head->next;
	position q = head->next;

	
		while(p->next != q && p->next->data != x){
			p = p->next;
		}
	return p;
	
}
position Find(position head, int x){
	position p = head->next;
	position q = head->next;

	
		while(p->next != q && p->next->data != x){
			p = p->next;
		}
	return p->next;
	
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

void DeleteTheElement(position head, int x){
	position p = Find(head, x);
	position q = FindPrev(head, x);
		q->next = p->next;
		free(p);

}
void DeleteAll(position head){
	position p = head->next;
	position next = NULL;
	while(p->next != head->next){
		next = p->next->next;
		free(p->next);
		p->next = next;	
	}
head->next = NULL;
}

void InsertAfter(position head, int x, int y){
	
	position p = Find(head, x);
	InsertAtStart(p, y);
}


void InsertBefore(position head, int x, int y){
	position p = FindPrev(head, x);
	InsertAtStart(p, y);
}


