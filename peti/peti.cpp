#include <stdio.h>
#include <malloc.h>

typedef struct list* position;
struct list{
	int element;
	position next;
}_LIST;

position CreateHeadNode();
position CreateNode(int);
void Insert(position, position);
void AddAtTheEnd(position, position);
void AddAtTheOrder(position, position);
position FindPrev(position, int);
void  DeleteElementByEle(position, int);
int ReadFromFile(char*, position);
void PrintElements(position);
position CopyElements(position firstHead);
void removeDuplicates(position head);
void stayDuplicate(position head);
void AddTwoLists(position headOne, position headTwo);
void Union(position, position, position);
void Intersection(position, position, position);
int main(void){
	position HeadOfFirstList = CreateHeadNode();
	position HeadOfSecondList = CreateHeadNode();	
	position Result1 = CreateHeadNode();
	position unionn = CreateHeadNode();
	position inter = CreateHeadNode();
	
	ReadFromFile("prvi.txt", HeadOfFirstList);
	ReadFromFile("drugi.txt", HeadOfSecondList);

	Result1 = CopyElements(HeadOfFirstList);
	AddTwoLists( Result1, HeadOfSecondList );
	PrintElements(Result1);	
	
	//result1 je nova lista unije
	printf("\n Unija skupva je:\n");
	removeDuplicates(Result1);
	
	PrintElements(Result1);
	
	printf("\n");
	
	Union(HeadOfFirstList, HeadOfSecondList, unionn);
	PrintElements(unionn);
	printf("\n");
	Intersection(HeadOfFirstList, HeadOfSecondList, inter);
	PrintElements(inter);
	
	free( HeadOfFirstList);
	free(HeadOfSecondList);
	free(Result1);
	free(inter);
	free(unionn);
	return 0;
}
position CreateHeadNode(){
	position q = (position)malloc(sizeof(_LIST));
	if(q == NULL) {
		printf("Losa alokacija memorije!");
		return NULL; //!!!
	}
	
	q->next = NULL;
	return q;
}
position CreateNode(int x){
	position q = (position)malloc(sizeof(_LIST));
	q->element = x;
	q->next = NULL;
	return q;
}
void Insert(position prev, position next){
	next->next = prev->next;
	prev->next = next;
}
//nepotrebno
void AddAtTheEnd(position head, position ele){
	position last = head;
	
	while(last->next != NULL)
	last = last->next;
	
	Insert(last, ele);
}
void AddAtTheOrder(position head, position element){
	
	if(head->next == NULL){
		Insert(head, element);
		return;
	}
	position tmp = head;
	
	while(tmp->next != NULL && tmp->next->element <= element->element){
		tmp = tmp->next;
		Insert(tmp, element);
		return;
		
}
Insert(head, element);
}
position FindPrev(position head, int ele){
	
	position q=head;
	head = head->next;
	while(head->next!=NULL && head->element != ele){
		q=head;
		head = head->next;
	}
	return q;
}
void  DeleteElementByEle(position head, int ele){
	
	position q=FindPrev(head, ele);

	position tmp = q->next->next; //to je sljedbenik elementa kojeg brisemo
	free(q->next);				//oslobodit ono sto brisem
	q->next = tmp;				//da prethodni ele onog sta smo obrisali pokazuje na sljedeci ele onog sta smo obrisali
}
int ReadFromFile(char* fileName, position head){
	FILE* f;
	int element;
	position q = NULL; // ne treban zauzimat memoriju jer dajen funk
	f = fopen(fileName, "r");
	if(f == NULL) return -1;
	
	while(!feof(f)){
	
		fscanf(f, " %d", &element);
		q = CreateNode(element);
		AddAtTheOrder(head, q);
		// NIKAD FREE!
		}
		
		fclose(f);
		
	return 0;
}
void PrintElements(position head){
	
	position ele = head->next;
	
	while( ele != NULL){
		printf("%d ", ele->element);
		ele = ele->next;
	}
}
position CopyElements(position firstHead)
{	position result =CreateHeadNode();
	position q = NULL;
	while(firstHead->next != NULL)
		{
			q = CreateNode(firstHead->next->element);
			AddAtTheEnd(result, q);
			firstHead->next = firstHead->next->next;
		}
return result;		
}


void removeDuplicates(position head)
{
	position a = head->next;

	while( a->next != NULL){
		// tu moram stavit da je b jer se tako  pomicemo
		position b = a->next;
		while(b->next != NULL){
			if(b->element == a->element)
				DeleteElementByEle(head, b->element);
			b = b->next;
		}
	a = a->next;
	}
}
void stayDuplicate(position head){
	position a = head->next;

	while( a->next != NULL){
		// tu moram stavit da je b jer se tako  pomicemo
		position b = a->next;
		while(b->next != NULL){
			if(!(b->element == a->element))
				DeleteElementByEle(head, b->element);
			b = b->next;
		}
	a = a->next;
	}
}

void AddTwoLists(position headOne, position headTwo){
	//neka mi headOne bude result1, a headTwo HeadOfSecondList
	position q = NULL;
	while(headTwo->next != NULL){
		q = CreateNode(headTwo->next->element);
		AddAtTheEnd(headOne, q);
		headTwo->next = headTwo->next->next;
	}
}
//isto kao suma kod polinoma
void Union(position head1, position head2, position un){
	position p = head1->next;
	position q = head2->next;
	position a = NULL;
	
	while(p != NULL && q != NULL){
		a = (position)malloc(sizeof(_LIST));
		if(p->element > q->element){
			a->element = p->element;
			p = p->next;
		}
		else if(p->element < q->element){
			a->element = q->element;
			q = q->next;
		}
		else{
			a->element = p->element;
		
			q = q->next;
			p = p->next;
		}
		Insert(un, a);
		un = a;
	}
position tmp;
	if(p == NULL)
	tmp = q;
	else
	tmp = p;
	while(tmp != NULL){
		a = (position)malloc(sizeof(_LIST));
		a->element = tmp->element;
		Insert(un,a);
		un = a;
		tmp = tmp->next;
	}
}
void Intersection(position head1, position head2, position inter){
	position p = head1->next;
	position q = head2->next;
	position a = NULL;
	
	while(p != NULL && q != NULL){
		if(p->element > q->element)
		p = p->next;
		else if(p->element < q->element)
		q = q->next;
		else{
			a = (position)malloc(sizeof(_LIST));
			a->element = p->element;
			p = p->next;
			q = q->next;
			
			Insert(inter, q);
			inter = q;
		}
	}
	
}



