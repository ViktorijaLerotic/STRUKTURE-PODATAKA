#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#define name1 "prvi.txt"
#define name2 "drugi.txt"
typedef struct poly* position;
struct poly{
	int coeff;
	int exp;
	position next;
}_POLY;
position CreateHeadNode();
position CreateNode(int, int);
void ReadFromFile(char*, position);
void Insert(position, position);
position Find(position head, int x);
position FindPrev(position head, int ele);
void DeleteElement(position head, int x);
void AddAtOrder(position, position);
void Print(position);
void sumPoly(position, position, position);
void MultyPoly(position first, position second, position multy);
int main(void){
	position first = CreateHeadNode();
	position second = CreateHeadNode();
	position multy = CreateHeadNode();
	position sum = CreateHeadNode();
	
	ReadFromFile(name1, first);
	ReadFromFile(name2, second);
	Print(first);
	printf("\n");
	Print(second);
		printf("\n");
	sumPoly(first, second, sum);
	Print(sum);
	MultyPoly(first, second, multy);
	printf("\n");
	Print(multy);
	
	free(first);
	free(second);
	free(sum);
	free(multy);
	return 0;
}
position CreateHeadNode(){
	position q = (position)malloc(sizeof(_POLY));
	if(q == NULL) {
		printf("Losa alokacija memorije!");
		return NULL; //!!!
	}
	
	q->next = NULL;
	return q;
}
position CreateNode(int x, int y){
	position q = (position)malloc(sizeof(_POLY));
	q->coeff = x;
	q->exp = y;
	q->next = NULL;
	return q;
}
void Insert(position Prev, position Next){
	Next->next = Prev->next;
	Prev->next = Next;
}
position Find(position head, int x){
	position p = head->next;
	while(p != NULL && p->exp != x)
	p = p->next;
return p;
}
position FindPrev(position head, int ele){
	
	position q=head;
	position p = head->next;
	while(p!=NULL && p->exp != ele){
		q=head;
		p = p->next;
	}
	return q;
}
//brisanje po exponentu
void DeleteElement(position head, int x){
	position q = Find(head, x);
	position p = FindPrev(head, x);
	p->next = q->next;
	free(q);
}
void AddAtOrder(position head, position element){
	position p = head;
	if(head->next == NULL){
		Insert(head, element);
		return;
	}
	
	
	while(p->next != NULL && p->next->exp > element->exp)
		p = p->next;
		//samo za koef uredivat:
		if( p->next != NULL && p->next->exp == element->exp){
			p->next->coeff = element->coeff;
			
			if(p->next->coeff == 0)
			DeleteElement(head, p->next->coeff);
			
		}
		else{
			Insert(p, element);
		return;
		}
		
	
		
	
Insert(head, element);	
}
void ReadFromFile(char* fileName, position head){
	FILE* f;
	int x, y;
	f = fopen(fileName, "r");
	while(!feof(f)){
		fscanf(f, "%d %d", &x, &y);
		AddAtOrder(head, CreateNode(x,y));
	}
	fclose(f);
}

void Print(position head){
	
	position ele = head->next;
	
	while( ele != NULL){
		printf("%d*x^%d", ele->coeff, ele->exp);
		ele = ele->next;
		if(ele != NULL)
		printf("+");
	}
}
void sumPoly(position head1, position head2, position sum){
	
	//stavljam na prave prve elemente
	position p = head1->next;
	position q = head2->next;
	
	// a mi je kucica u koju cu stavljat onaj element p ili q ili p+q koji zadovoljava uvjet
	position a = NULL;
	while(p != NULL && q != NULL){
		
		//mora biti tu jer samo tu vrijedi
		a = (position)malloc(sizeof(_POLY));
		if(p->exp == q->exp){
			a->coeff = p->coeff + q->coeff;
			a->exp = p->exp;
			//pomicanje sa oba
			p = p->next;
			q = q->next;
		}
		else if(p->exp > q->exp){
				a->coeff = p->coeff;
				a->exp = p->exp;
				//pomicanje samo onog veceg
			p = p->next;
		}
		else{
			a->coeff = q->coeff;
			a->exp = q->exp;
			q = q->next;
		}
		Insert(sum, a);
		// !!!!!!
		sum = a;
		
	}
	position tmp;
	if(p == NULL)
	tmp = q;
	else
	tmp = p;
	while(tmp != NULL){
	a = (position)malloc(sizeof(_POLY));
	a->coeff = tmp->coeff;
	a->exp = tmp->exp;
		Insert(sum, a);
		sum = a;
	tmp = tmp->next;
	}
}
void MultyPoly(position first, position second, position multy){
	position i, j, tmp, q;
	i = first->next;
	
	//ovakva konstrukcija while petlji sa pomicanjem je kao ugnjezdena for petlja
	while(i != NULL){
		j = second->next;
		while(j != NULL){
			q = (position)malloc(sizeof(_POLY));
			
			q->coeff = i->coeff + j->coeff;
			q->exp = i->exp * j->exp;
			
			tmp = multy;
			// isti dio kao kod sortiranja pri unosu
			while(tmp->next != NULL && tmp->next->exp > q->exp)
			tmp = tmp->next;
			
			if( tmp->next != NULL && tmp->next->exp == q->exp){
			tmp->next->coeff = q->coeff;
		
			if(tmp->next->coeff == 0)
			DeleteElement(second, tmp->next->coeff);
			
		}
		else{
		Insert(tmp, q);
		return;
		}
		
		j = j->next;
		}
		i = i->next;
	}
}

