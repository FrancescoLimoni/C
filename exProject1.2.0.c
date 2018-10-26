/*
	Project 2/3 V2.0
	 fgets version.

	make a book library composte to:
	 - Isbn
	 - Title
	 - Author
	 - Three keyword.
	----------------------------------
	Problem:
	 - see function.
	 - delete function.
	 - add function.  
	 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  #define maxSpace 40
  #define maxWord 15


struct cube{
	char isbn[maxSpace];
	char title[maxSpace];
	char author[maxSpace];
	char wordF[maxWord];
	char wordS[maxWord];
	char wordT[maxWord];
	struct cube *next;
};


void vallet();
void valletII();
//void valletIII(struct cube *);
void fixBuffer(char *);

//------------------------------

void makeBook(struct cube *);
void search(struct cube *);
void see(struct cube *);
void delete(struct cube *, struct cube **);


int main(void)
{	
	struct cube *head;
	struct cube *book;
	struct cube *walk;
	struct cube *tail;
	int decision;
	char empty[2];

	head = NULL;
	system("clear");
	vallet();
	printf("your decision: ");
	  scanf("%d", &decision);
	  fgets(empty, 2, stdin);
	  system("clear");

	while(decision != 0){
		switch(decision){
			case 1:
				book = (struct cube *)malloc(sizeof(struct cube));
				printf("--------------------------ADD SESION--------------------------");
				makeBook(book);
				if(head == NULL){
					head = book;
					walk = head;
				}else{
					walk->next = book;
					walk = book;
				}//end if-else head.
			break;

			case 2:
				printf("\n-------------------------SEARCH SESION-------------------------");
				walk = head;
				search(walk);
			break;

			case 3:
				printf("\n--------------------------SEE SESION--------------------------\n");
				walk = head;
				see(walk);
			break;

			case 4:
				printf("\n-------------------------DELETE SESION-------------------------");
				delete(book, &head);
				walk = head;
				see(walk);
			break;
		}//end switch decision.
		
		valletII();
		printf("\nyour decision: ");
	 	 scanf("%d", &decision);
	 	 fgets(empty, 2, stdin);
	 	 system("clear");
	 	 //printf("->%d<-\n", decision);
	}//end 



	printf("\n\n\n");
	return 0;
}

void vallet(){
	printf("\t\t\tWELCOME TO YOUR LIBRARY\n");
	printf("\t\t1=ADD, 2=SRC, 3=SEE, 4=DELETE, 0=EXIT\n");
	printf("------------------------------------------------------------------\n");
}//end Vallet.

void valletII(){
	printf("\n\n\n\n\n\n\n\t\t\tYOUR LIBRARY\n");
	printf("\t\t1=ADD, 2=SRC, 3=SEE, 4=DELETE, 0=EXIT\n");
	printf("------------------------------------------------------------------\n");
}//end valletII.

/*void valletIII(struct cube *){

	int i = 0;

	while(i != 4){
		printf("[%s - %s - %s]", walk->isbn, walk->title, walk->author);
		printf("\n-----------------------------------------\n");
		walk = walk->next;
		i++;

		if(walk == NULL)
			break;
	}
}*/

void fixBuffer(char *a){
	int len;

	len = strlen(a);
	if(a[len-1] == '\n'){
		a[len-1] = 0;
		//printf("\nafter fix inside funtion: ->%s<-", a);
	}//end if.
}//end fixBuffer.

//------------------------------------

void makeBook(struct cube *book){
 	
	printf("\n\n[BOOK INFO]\n");
		printf("type a isbn: ");
			fgets(book->isbn, maxWord, stdin);
			fixBuffer(book->isbn);
			//printf("->%s<-", book->isbn);
		printf("type a title: ");
			fgets(book->title, maxSpace, stdin);
			fixBuffer(book->title);
			//printf("->%s<-", book->title);
		printf("type a author: ");
			fgets(book->author, maxSpace, stdin);
			fixBuffer(book->author);
			//printf("->%s<-", book->author);

	printf("\nKEYWORD INFO:\n");
		printf("type first keyword: ");
			fgets(book->wordF, maxWord, stdin);
			fixBuffer(book->wordF);
		printf("type second keyword: ");
			fgets(book->wordS, maxWord, stdin);
			fixBuffer(book->wordS);
		printf("type third keyword: ");
			fgets(book->wordT, maxWord, stdin);
			fixBuffer(book->wordT);  
}//end makeBook.

void search(struct cube *walk){

	char src[maxWord];
	int valWordF;
	int valWordS;
	int valWordT;
	int count = 0;

	printf("\ntype one keyword: ");
	  fgets(src, maxWord, stdin);
	  fixBuffer(src);
	  printf("\n");

	while(walk != NULL){
	   	valWordF = strcmp(walk->wordF, src);
	   	valWordS = strcmp(walk->wordS, src);
	   	valWordT = strcmp(walk->wordT, src);

	   	if(valWordF == 0){
	   		printf("Find something: %s - %s - %s\n", walk->isbn, walk->title, walk->author);
	   		count++;
	   	}else if(valWordS == 0){
	   		printf("Find something: %s - %s - %s\n", walk->isbn, walk->title, walk->author);
	   		count++;
	   	}else if(valWordT == 0){
	   		printf("Find something: %s - %s - %s\n", walk->isbn, walk->title, walk->author);
	   		count++;
	   	}

	   	walk = walk->next;
	}//end while walk.
	
	if(count == 0)
		printf("Sorry, there isn't match!");
}//end search.

void see(struct cube *walk){
	
	int count = 0;

	while(walk != NULL){
		printf("%d| %s - %s - %s", count+1, walk->isbn, walk->title, walk->author);
		printf("\n-----------------------------------------\n");
		
		count++;
		/*----------------------------------------------------------	
		if(walk == NULL && count == 0){
			printf("NO BOOK INSEDE OF LIBRARY");	
		}else{
			break;
		}//if walk.
		*/
		walk = walk->next;
	}// end while i.
}//end see.

void delete(struct cube *book, struct cube **head){
	
	struct cube *a;
	struct cube *b;
	char del[maxSpace];
	int valDel;

	printf("\ntype book title that you would delete: ");
	  fgets(del, maxSpace, stdin);
	  fixBuffer(del);

	

	  a = *head;
	  b = *head;

	  while(a != NULL){
		valDel = strcmp(del, a->title);
		
		if(valDel == 0){
			
			if(a == *head){
				
				*head = a->next;
				printf("you have deleted: %s\n\n", a->title);
				free(a);
 //-----------------------------------------------------------------------			
			}else{
				
				b = *head;
				
				while(b != a-1){
					b = b->next;
					//printf("b: %s ", b->title);
				}//end while b.
				
				b->next = a->next;
				//printf("\nb: %s c: %s", b->title, c->title);
			}//end if-else head.
		}//end if valDel.
		a = a->next;
	}//end while a.

	/*
		a = *head;
		while(a != NULL){
			printf("%s - ", a->title);
			a = a->next;
		}  
	*/ 

}//end delete.