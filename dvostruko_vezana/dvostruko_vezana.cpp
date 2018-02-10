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
void Insert(position, position);
void AddAtBeginning(position, position);
void AddAtTheEnd(position, position);
void InsertUsersDataAtBegginingOfList(position);
void InsertUsersDataAtTheEndOfList(position);
void PrintElement(position);
void PrintElements(position);
position FindTheElement(position, int);
position FindPrev(position, int);
void DeleteTheElement(position, int);
void DeleteAllElements(position);
int main(){
	position head = CreateHeadNode();
	
	InsertUsersDataAtTheEndOfList(head);
	InsertUsersDataAtBegginingOfList(head);
	InsertUsersDataAtTheEndOfList(head);
	InsertUsersDataAtBegginingOfList(head);
	InsertUsersDataAtTheEndOfList(head);
	PrintElements(head);
	DeleteTheElement(head, 2);
	PrintElements(head);
	position find = FindPrev(head, 3);
	printf("\n");
	PrintElement(find);
	printf("\n");
	DeleteAllElements(head);
	PrintElements(head);
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

void Insert(position Prev, position Next){
	if(Prev->next == NULL){
	Next->prev = Prev;
	Next->next = NULL;
	Prev->next = Next;
	}
	else{
	Next->prev = Prev;
	Next->next = Prev->next;
	(Prev->next)->prev = Next;
	Prev->next = Next;	
	}
}
void AddAtBeginning(position head, position element){
	Insert(head, element);
}

void InsertUsersDataAtBegginingOfList(position head){
	int x;
	printf("Unesite neki broj koji zelite unjeti na pocetak liste:\n");
	scanf("%d", &x);
	position q = NULL;
	q = CreateNode(x);
	AddAtBeginning(head, q);
}

void AddAtTheEnd(position head, position element){
	position last = head;
	while(last->next != NULL){
		last = last->next;
	}
	
	Insert(last, element);
}

void InsertUsersDataAtTheEndOfList(position head){
	int x;
	printf("Unesite neki broj koji zelite unjeti na kraj liste:\n");
	scanf("%d", &x);
	position q = NULL;
	q = CreateNode(x);
	AddAtTheEnd(head, q);
}

void PrintElement(position element){
	printf("%d", element->data);
}
void PrintElements(position head){
	position element = head->next;
	while(element != NULL){
		printf("%d\n", element->data);
		element=element->next;
	}
}

position FindTheElement(position head, int x){
	position ele = head;
	while(ele->next != NULL && ele->data != x){
		ele = ele->next;
	}
return ele;	
}
position FindPrev(position head, int x){
	position q = FindTheElement(head, x);
	return q->prev;
}
void DeleteTheElement(position head, int x){
/*	position q = NULL;
	position tmp = NULL;
	position tmp2 = NULL;
	q = FindTheElement(head,x);
	tmp = q->next;
	tmp2 = q->prev;
	(q->prev)->next = tmp;
	free(q);
	tmp->prev = tmp2;*/
	
	position q = FindTheElement(head, x);
	q->prev->next = q->next;
	q->next->prev = q->prev;
	free(q);
	
}
void DeleteAllElements(position head){
	position p = head->next;
	position next;
	while (p != NULL){
		next = p->next ;
		free(p);
		p = next;
	}
head->next = NULL;	
}
