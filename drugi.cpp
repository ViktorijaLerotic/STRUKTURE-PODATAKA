#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct person* position;
typedef struct person{
	char firstName[20];
	char lastName[20];
	int year;
	position next;
	
}_PERSON;

position CreateHeadNode();
position CreateNode(char*, char*, int);
void InsertBefore(position, char*, position);
void InsertAfter(position, char*, position);
void Insert(position, position);
void AddAtTheBeggining(position, position);
void AddToTheEnd(position, position);
void PrintElementOfList(position);
void PrintElementsOfList(position);
position SearchTheElementByLastName(position, char*);
position FindPrev(position, char*);
void DeleteElementBySurename(position, char*);
void InsertUsersDataAtBegginingOfList(position);
void InsertUsersDataAtEndOfList(position);
void TheChoice(position);
void PrintToList(position, char*);
void ReadFromList(position, char*);

int main(){
	
	position head = CreateHeadNode();
	TheChoice(head);
	free(head);
	
	return 0;
}
position CreateHeadNode(){
	
	position q = NULL;
	q=(position)malloc(sizeof(_PERSON));
	if(q==NULL) return NULL;
	
	q->next=NULL;
	return q;
}
//u jedan "vagon" vezane liste, strukturu, ubacujem podatke-ime, prezime, god rodenja
position CreateNode(char* firstName, char* lastName, int year){
	
	position q = NULL;
	q=(position)malloc(sizeof(_PERSON));
	
	strcpy(q->firstName, firstName);
	strcpy(q->lastName, lastName);
	q->year=year;
	
	q->next=NULL;
	return q;
}
//ubacujem novi element izmedu 2 postojeca elementa(bilo koja dva ele)
void Insert(position prev, position next){
	
	next->next=prev->next;
	prev->next=next;
}
void AddAtTheBeggining(position head, position element){
	
	Insert(head, element);
}
void AddAtTheEnd(position head, position element){
	
	position last=head;
	//trazim zadnji element
	while(last->next!=NULL)
		last=last->next;
	Insert(last, element);
}
void PrintElementsOfList(position head){
	
	//obavezno ispisivat od 1.pravog clana a ne heada jer ostane neko "smece"
	position elements=head->next; //!!!!!!!!!!
	if(elements==NULL){
		printf("Vezana lista je prazna!");
		return;
	}
	while(elements!=NULL){
		printf("%s\t%s\t%d\n", elements->firstName, elements->lastName, elements->year);
		//prebaciti na novi element obavezno!!
		elements=elements->next;
	}
}
void PrintElementOfList(position element){
	
		printf("%s\t%s\t%d\n", element->firstName, element->lastName, element->year);	
}
position SearchTheElementByLastName(position head, char* lastName){
	
	position q = head->next;
	while(q!=NULL){
		if(strcmp(q->lastName, lastName)==0)
		return q;
		else
		q = q->next;
	}
}
position FindPrev(position head, char* surname){
	
	position q=head;
	head = head->next;
	while(head->next!=NULL && strcmp(head->lastName, surname)!=0){
		q=head;
		head = head->next;
	}
	return q;
}
void DeleteElementBySurename(position head, char* surname){
	
	position q=FindPrev(head, surname);

	position tmp = q->next->next; //to je sljedbenik elementa kojeg brisemo
	free(q->next);				//oslobodit ono sto brisem
	q->next = tmp;				//da prethodni ele onog sta smo obrisali pokazuje na sljedeci ele onog sta smo obrisali
}
void InsertAfter(position head, char* surname, position q){
	
	position w =  SearchTheElementByLastName(head, surname); //pronasla element iza kojeg postavljam novi element
	Insert(w,q);
}
void InsertBefore(position head, char* surname, position q){
	
	position w = FindPrev(head, surname);
	Insert(w,q);
}
void PrintToList(position head, char* fileName){
	FILE* fp;
	fp = fopen(fileName, "w");
	if(fp == NULL) return;
	
	position q=head->next;
	
	while(q!=NULL){
		fprintf(fp, "\n%s\t%s\t%d\n", q->firstName, q->lastName, q->year);
		q = q->next;
	}
	fclose(fp);
}
void ReadFromList(position head, char* fileName){
	FILE* fp;
	int year;
	char firstName[50], lastName[50];
	char buffer[150];

	fp = fopen(fileName, "r");
	if (fp == NULL) return;

	while (!feof(fp))
	{
		fgets(buffer, 150, fp);
		if (strlen(buffer) > 0)
		{
			sscanf(buffer, "%s %s %d", firstName, lastName, &year);
			AddAtTheEnd(head, CreateNode(firstName, lastName, year));
			//kopira u buffer, od nulte pozicije, onoliko bitova koliko je duljina buffera
			memset(buffer, 0, strlen(buffer));
		}		
	}
	fclose(fp);
}
void InsertUsersDataAtBegginingOfList(position head){
	char name[20];
	char surname[20];
	int year;
	position element=NULL;
	
	printf("Unesite podatke o osobi na sljedeci nacin:\nime\t\tprezime\t\tgodina rodenja:\n");
	scanf("%s %s %d", name, surname, &year);
	
	element=CreateNode(name, surname, year);
	AddAtTheBeggining(head, element);	
}
void InsertUsersDataAtEndOfList(position head){
	char name[20];
	char surname[20];
	int year;
	position element=NULL;
	
	printf("Unesite podatke o osobi na sljedeci nacin:\nime\t\tprezime\t\tgodina rodenja:\n");
	scanf("%s %s %d", name, surname, &year);
	
	element=CreateNode(name, surname, year);
	AddAtTheEnd(head, element);
}
void TheChoice(position head){
	char name[20];
	char surname[20];
	int year;
	position element=NULL;
	int i=0;
	int choice;

	char* choices[]={"1. Novi element na pocetak liste","2. Ispis liste","3. Novi element na kraj liste","4. Pronadi element u listi (po prezimenu)", "5. Brise element po prezimenu", "6. Novi element iza zeljenog","7. Novi element ispred zeljenog","8. Ispis liste u datoteku","9. Iscitaj listu iz datoteke","10. Izlaz iz menija"};
	printf("     Odaberite zeljenu radnju:\n\n");
	
	for(i=0;i<10;i++)
		printf("%s\n", choices[i]);
		
	scanf("%d", &choice);
	i=0;
	
		if(choice == (i+1)){
			InsertUsersDataAtBegginingOfList(head);
			TheChoice(head);
		}
		else if(choice == (i+3)){
			InsertUsersDataAtEndOfList(head);
			TheChoice(head);
		}
		else if(choice == (i+2))
		{
			PrintElementsOfList(head);
			TheChoice(head);
		}
		else if(choice == (i+4)){
			printf("Unesite zeljeno prezime po kojem cemo pretraziti:\n");
			scanf("%s", surname);
			PrintElementOfList(SearchTheElementByLastName(head, surname));
			TheChoice(head);
		}
		else if(choice == (i+5)){
			printf("Unesite zeljeno prezime koje cemo izbrisati:\n");
			scanf("%s", surname);
			DeleteElementBySurename(head, surname);
			TheChoice(head);
		}
		else if(choice == (i+6)){
			printf("Unesite zeljeno prezime iza kojeg nadodajemo novo-kreirani element:\n");
			scanf("%s", surname);
			printf("Unesite podatke o osobi na sljedeci nacin:\nime\t\tprezime\t\tgodina rodenja:\n");
			scanf("%s %s %d", name, surname, &year);
			element=CreateNode(name, surname, year);
			InsertAfter(head,surname,element);
			TheChoice(head);
		}
		else if(choice == (i+7)){
			printf("Unesite zeljeno prezime ispred kojeg nadodajemo novo-kreirani element:\n");
			scanf("%s", surname);
			printf("Unesite podatke o osobi na sljedeci nacin:\nime\t\tprezime\t\tgodina rodenja:\n");
			scanf("%s %s %d", name, surname, &year);
			element=CreateNode(name, surname, year);
			InsertBefore(head,surname,element);
			TheChoice(head);
		}
		else if(choice == (i+8)){
			PrintToList(head, "lista.txt");
			TheChoice(head);
		}
		else if(choice == (i+9)){
			ReadFromList(head, "lista.txt");
			TheChoice(head);
		}
		else if(choice == (i+10))
			printf("\nOvo je izlaz iz menija!\n");
		else{
			printf("Nije odabran pravi izbor!\n");	
			TheChoice(head);
		}
}

