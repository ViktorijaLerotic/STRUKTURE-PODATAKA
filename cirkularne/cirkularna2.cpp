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
void AddAtStart(position, int);
void AddAtEnd(position, int);
void InsertBefore(position, int, int);
void InsertAfter(position, int, int);
void Print(position);
position FindPrev(position, int);
position Find(position, int);
void DeleteEle(position, int);
void DeleteAll(position);
int main(void){
	position head = CreateHeadNode();

	AddAtStart(head, 3);
	AddAtStart(head, 8);
	AddAtStart(head, 11);
	AddAtEnd(head, 20);
	AddAtEnd(head, 111);
	InsertAfter(head, 3, 4);
	InsertBefore(head, 20, 18);
	DeleteEle(head, 111);
	Print(head);
	position p = Find(head, 8);
	position q = FindPrev(head, 111);
	printf("\nTrazeni je %d\n", p->data);
	printf("prethodni trazenoga je %d\n", q->data);
	DeleteAll(head);
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
void AddAtEnd(position head, int x){
	position q = CreateNode(x);
	position last = GetLastElement(head);
	
	if(head->next == NULL)
		head->next = q;
		else{
			q->next = last->next;
			last->next = q;
			q->prev = last;
		}
}
position Find(position head, int x){
	position p = head->next;
	position q = head->next;

while(p->next != q && p->next->data != x){
			p = p->next;
		}
	return p->next;
}
position FindPrev(position head, int x){
	position q = Find(head, x);
	return q->prev;
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
void InsertBefore(position head, int x, int y){
	position q = FindPrev(head, x);
	AddAtStart(q, y);
}
void InsertAfter(position head, int x, int y){
	position q = Find(head, x);
	AddAtStart(q, y);
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
void DeleteEle(position head, int x){
	position p = Find(head, x);
	position q = p->prev;
	
	q->next = p->next;
	p->next->prev = q;
	free(p);
}
