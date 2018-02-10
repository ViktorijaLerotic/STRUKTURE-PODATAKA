//Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
//omoguæiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
//nekog elementa.
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree* position;
struct tree{
	int value;
	position left;
	position right;
}_TREE;

void ReadFromFile(position root, char* fileName);
position CreateSubTree(int);
position InsertElement(position, int);
position FindMax(position);
position FindMin(position);
position FindElement(position, int);
position DeleteElement(position , int);

void Menu(position);
void DeleteAllElements(position);
void PrintTreeInOrder(position);
void PrintElement(position);
void Options();
int main(void){
	position root = NULL;
	Menu(root);
	
	return 0;
}


position CreateSubTree(int x){
	position q = (position)malloc(sizeof(_TREE));
	if(q == NULL) return NULL;
	
	q->value = x;
	q->left = NULL;
	q->right = NULL;
	
	return q;
}

// unosenje novog elementa
position InsertElement(position root, int x){

	// 1) ako nemam nijedan element
	if(root == NULL){
	root = CreateSubTree(x);
	}
		
	// 2) ako postoji prvi clan i ako je x manji od prvog clana-ide na lijevu stranu
	else if(x < root->value){
		
		root->left = InsertElement(root->left, x);
	}
	// 3) ako postoji prvi clan i ako je x veci od prvog clana-ide na desnu stranu
	else if(x > root->value){
	
		root->right = InsertElement(root->right, x);
	}
	
	return root;
}
// ispisivanje stabla
void PrintTreeInOrder(position t)
{
    if(t==NULL)  return;
	printf("%d\n",t->value);
    PrintTreeInOrder(t->left);
    PrintTreeInOrder(t->right);
   
}
void PrintElement(position element){
	if(element == NULL) return;
	
	printf("Trazeni element za ispis je: %d\n", element->value);
}
//pronalazak nekog elementa
position FindElement(position root, int x){

	if(root == NULL) return NULL;
	//!!!!!!!!!!! moram return rekurzvinu f-ju
	else if(root->value > x)
	return FindElement(root->left, x);
	else if (root->value < x)
		return FindElement(root->right, x);
	
return root;
}
// pronalazak minimalnog-s lijeve strane je
position FindMin(position root){
	while(root->left != NULL)
		root = root->left;
	return root;	
}

// pronalazak maksimalnog-s desne strane je
position FindMax(position root){
	while(root->right != NULL)
		root = root->right;
	return root;	
}
// brisanje elemenata

position DeleteElement(position root, int x){
	
	if(root == NULL) return NULL;
	
	else if(root->value > x)
		root->left = DeleteElement(root->left, x);
	else if(root->value < x)
		root->right = DeleteElement(root->right, x);
		
	else if(root->left != NULL && root->right != NULL){
		root->value = FindMin(root->left)->value;
		root->right = DeleteElement(root->right, root->value);
	}
	
	else{
		position current = root;
		if(root->left != NULL){
			root = root->left;
		}
		else
		{
			root = root->right;
		}
	free(current);	
	}
	
return root;	
}
void DeleteAllElements(position root){
	if(root != NULL) 
	
	{DeleteAllElements(root->right);
		DeleteAllElements(root->left);
		
		free(root);
	}
}
void ReadFromFile(position root, char* fileName){
	FILE* f;
	f = fopen(fileName, "r");
	
	if( f == NULL ) return;
	
	
	int x;
	while(!feof(f)){
		
		fscanf(f, "%d ", &x);
		root = InsertElement(root, x);
		
	}
	
	
	fclose(f);
}

void Options(){
	
	printf("Dobro dosli u izbornik!\n");
	printf("Slijedece opcije su:\n");
	printf("1. Unos novih podataka u strukturu namijenjnu za pretrazivanje iz filea.\n");
	printf("2. Ispis svih podataka iz iste struktre.\n");
	printf("3. Pronalazak zeljenog elementa unutar strukture.\n");
	printf("4. Brisanje odredenog elementa iz strukture.\n");
	printf("5. Izlaz.\n");
}
void Menu(position root){
	int c,x,y;
	position q = NULL;
	Options();
	printf("Vas odabir je:\n");
	scanf("%d", &c);
	switch(c){
		case 1:	printf("Unjet ce se podaci iz filea:\n");
				ReadFromFile(root,"brojevi.txt");	
				break;
		case 2: PrintTreeInOrder(root);
				break;
		case 3:  printf("Unesite podatak koji zelite pronaci:\n");
				scanf("%d", &y);
				PrintElement(FindElement(root, y));
				break;
		case 4: printf("Unesite podatak koji zelite izbrisati:\n");
				scanf("%d", &x);
				root = DeleteElement(root, x);
				break;

		case 5: return;
				break;
	}
	Menu(root);
}
