/*
	Project 3/3 V2.1
	 fgets version.
	 Write/read file version.

	make a book library composte to:
	 - Isbn
	 - Title
	 - Author
	 - Three keyword.
	----------------------------------
	Problem: 
	- sometimes buffer problem into file 359 row.
	 
*/

/* Define a statement 
 Includo le funzioni di base */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the space identify with maxSpace and maxWord 
   Definisco lo spazio identificato da maxSpace e maxWord */
#define maxSpace 45
#define maxWord 20

/* Define a struct cube with that field 
   Definisco lo struct cube con i seguenti campi */
struct cube{
	char isbn[maxSpace];
	char title[maxSpace];
	char author[maxSpace];
	char wordF[maxWord];
	char wordS[maxWord];
	char wordT[maxWord];
	struct cube *next;
};

/* I have declared the functions made by myself 
   Ho dichiarato le funzioni fatte da me stesso */
void vallet();
void valletII();
void fixBuffer(char *);
void oldLibrary(struct cube *, FILE *);
void putIn(FILE *, struct cube *walk);
void makeBook(struct cube *, FILE *fp);
void search(struct cube *);
void see(struct cube *, struct cube *head);
void delete(struct cube *, struct cube **);


/* Start of Program 
   Inizio del Programma */
int main(void)
{	
	/* variables declare  
	   Dichiarazione delle variabili */
	struct cube *head;
	struct cube *book;
	struct cube *walk;
	struct cube *end;
	char momentary[maxSpace];
	char empty[2];
	int decision;
	int count;
	FILE *fp;
	
	/* Variables Initialize 
	   Inizializzo le variabili */
	head = NULL;
	count = 0;

	/* cleaning of shell, open fp file reading mode and carry out a check of existence 
	   pulizia della shell, apertura del file fp in modalità lettura e controllo esistenza  */
	system("clear");
	fp = fopen("testProject1.1.4.text", "r");

	if(fp != NULL){
		++count;
		
		/* while loop to resolve a little buffer problem and for see old library 
		   ciclo while per risolvere un piccolo problema di buffer */
		while(1){
			if(feof(fp)){
				
				end = end - 1;
				walk = head;
				//printf("\nEnd: %s",end->title);

				while(walk != end){
					walk = walk->next;
				}//end while walk.
				
				end = walk->next;
				free(end);

				walk->next = NULL;
				end = walk;
			
				break;
			}//end if feof.

			book = (struct cube *)malloc(sizeof(struct cube));
			oldLibrary(book, fp);
				
	      	if(head == NULL){
				head = book; 
				walk = head;
				end = walk;
			}else{
				end->next = book;
				end = book;
			}//end if-else head.
			
		}//end while 1.

		printf("\t\t\t WELCOME BACK");
		printf("\n--------------------------OLD SESION--------------------------\n");
		printf("\t\t " " [ isbn - title - author ]\n\n\n\n");
		
		while(walk != NULL){
			end = walk;
			walk = walk->next;
		}
	
		walk = head;
		while(walk != NULL){
			
			printf("%s - %s - %s", walk->isbn, walk->title, walk->author);
			printf("\n--------------------------------------------------------------\n");
			walk = walk->next;

		}//end while.
		
		fclose(fp);	
	}//end if fp.

	/* if control statement to get know if there was an old library and opening fp file writing mode 
	   Struttura di controllo if per sapere se c'era una libreria vecchia e apertura del file fp in modalita scrittura */
	if(count == 0){
		fp = fopen("testProject1.1.4.text", "w");
		
		system("clear");
		vallet();

		printf("your decision: ");
		  scanf("%d", &decision);
		  fgets(empty, 2, stdin);

	}else{

		valletII();
		printf("\nyour decision: ");
		  scanf("%d", &decision);
		  fgets(empty, 2, stdin);
	}//end if-else count.

	system("clear");
	
	/* "Option menu" 1= add, 2= search, 3= see, 4= delete and 0= exit 
	    "menu opzioni" 1= aggiungere, 2= cercare, 3= vedere, 4=eliminare e 0= uscire*/
	while(decision != 0){
		switch(decision){
			case 1:
				
				fp = fopen("testProject1.1.4.text", "r");
				walk = head;
				while(walk != NULL){
					
					oldLibrary(book, fp);
					walk = walk->next;
				}//end while walk. 
				
				fclose(fp);

				fp = fopen("testProject1.1.4.text", "w");
				walk = head;
				while(walk != NULL){

					putIn(fp, walk);
					walk = walk->next;
				}//end while walk.
				

				book = (struct cube *)malloc(sizeof(struct cube));
				system("clear");
				printf("--------------------------ADD SESION--------------------------");

				if(fp == NULL)
					printf("\nPROBLEM OPENING FILE!");

				makeBook(book, fp);
				
				if(head == NULL){
					head = book;
					walk = head;
					end = walk;
				}else{
					end->next = book;
					end = book;
				}//end if-else head.

				fclose(fp);
			break;

			case 2:
				system("clear");
				printf("\n--------------------------SEARCH SESION--------------------------");
				printf("\n\t " " [ type the keyword that you would see ]\n\n\n");
				walk = head;
				search(walk);
			break;

			case 3:
				system("clear");
				printf("\n--------------------------SEE SESION--------------------------\n");
				printf("\t\t " " [ isbn - title - author ]\n\n\n\n");
				walk = head;
				see(walk, head);
			break;

			case 4:
				system("clear");
				printf("\n-------------------------DELETE SESION-------------------------");
				delete(book, &head);
				walk = head;
				printf("\n\n");
				see(walk, head);
				printf("\n\n");

				fp = fopen("testProject1.1.4.text", "r");
				
				walk = head;
				while(walk != NULL){
					
					oldLibrary(book, fp);
					
					walk = walk->next;
				}//end while walk. 
				
				fclose(fp);
				
				fp = fopen("testProject1.1.4.text", "w");
				walk = head;
				while(walk != NULL){

					putIn(fp, walk);
					walk = walk->next;

				}//end while walk.
				fclose(fp);
			break;	

			default:
				valletII();
				printf("\nyour decision: ");
		  		  scanf("%d", &decision);
		 		  fgets(empty, 2, stdin);
		 	break;

		}//end switch decision.
		
		valletII();
		printf("\nyour decision: ");
		  scanf("%d", &decision);
		  fgets(empty, 2, stdin);

	}//end while decision.

	fclose(fp);
	printf("\n\n\n");
	return 0;
}//end main.



/* First "user interface" with welcome message 
   prima "interfaccia virtuale" con un messaggio di benvenuto */
void vallet(){

	printf("\n--------------------------WELCOME TO YOUR LIBRARY--------------------------\n");
	printf("\t\t1=ADD, 2=SRC, 3=SEE, 4=DELETE, 0=EXIT\n");
}//end Vallet.


/* Second "user interface" 
   Seconda interfaccia virtuale */
void valletII(){

	printf("\n\n\n\n\n\n\t\t\t " " YOUR LIBRARY\n");
	printf("\t\t1=ADD, 2=SRC, 3=SEE, 4=DELETE, 0=EXIT\n");
	printf("------------------------------------------------------------------\n");
}//end valletII.

/* function that resolve fgets buffer problem 
   funzione che risolve il problema del buffer creato dalla fgets */
void fixBuffer(char *a){
	int len;

	len = strlen(a);
	if(a[len-1] == '\n'){
		a[len-1] = 0;
		//printf("\nafter fix inside funtion: ->%s<-", a);
	}//end if.
}//end fixBuffer.

/* function coping fields file into local varible 
   funzione che copia i cmapi dal file */
void oldLibrary(struct cube *book, FILE *fp){

	char momentary[maxSpace];

	fgets(momentary, maxSpace, fp);//extract string from file
	  fixBuffer(momentary);//fix string
	  strcpy(book->isbn, momentary);//string copy with book->isbn

	fgets(momentary, maxSpace, fp);
	  fixBuffer(momentary);
	  strcpy(book->title, momentary);

	fgets(momentary, maxSpace, fp);
	  fixBuffer(momentary);
	  strcpy(book->author, momentary);

	fgets(momentary, maxWord, fp);
	  fixBuffer(momentary);
	  strcpy(book->wordF, momentary);

	fgets(momentary, maxWord, fp);
	  fixBuffer(momentary);
	  strcpy(book->wordS, momentary);  

	fscanf(fp, "%s", momentary);
	  fixBuffer(momentary);
	  strcpy(book->wordT, momentary);	  
}//end oldLibrary.

/* function writing into file
   funzione che scrive sul file */
void putIn(FILE *fp, struct cube *walk){
	
	fputs(walk->isbn, fp);//writing walk->isbn into file
	  fprintf(fp, "\n");//make return command after walk->isbn 
	  
	fputs(walk->title, fp);
	  fprintf(fp, "\n");
	  
	fputs(walk->author, fp);
	  fprintf(fp, "\n");
	  
	fputs(walk->wordF, fp);
	  fprintf(fp, "\n");
	  
	fputs(walk->wordS, fp);
	  fprintf(fp, "\n");
	  
	fputs(walk->wordT, fp);
	  fprintf(fp, " ");//make blank space after walk->wordT
	  
}//end putIn.

/* function that fills struct fields from keyboard
   funzione che riempe i campi della struct da tastiera */
void makeBook(struct cube *book, FILE *fp){

	char empty[2];
 	
	printf("\n\n[BOOK INFO]\n");
		printf("type a isbn: ");
			fgets(book->isbn, maxWord, stdin);
			fixBuffer(book->isbn);
			fputs(book->isbn, fp);//method to put a string into file.
			fprintf(fp, "\n");//method to put a space into file.

		printf("type a title: ");
			fgets(book->title, maxSpace, stdin);
			fixBuffer(book->title);
			fputs(book->title, fp);//method to put a string into file.
			fprintf(fp, "\n");;//method to put a space into file.
	
		printf("type a author: ");
			fgets(book->author, maxSpace, stdin);
			fixBuffer(book->author);
			fputs(book->author, fp);//method to put a string into file.
			fprintf(fp, "\n");//method to put a return into file.
			
	printf("\nKEYWORD INFO:\n");
		printf("type first keyword: ");
			fgets(book->wordF, maxWord, stdin);
			fixBuffer(book->wordF);//method to put a string into file.
			fputs(book->wordF, fp);
			fprintf(fp, "\n");//method to put a return into file.

		printf("type second keyword: ");
			fgets(book->wordS, maxWord, stdin);
			fixBuffer(book->wordS);//method to put a string into file.
			fputs(book->wordS, fp);
			fprintf(fp, "\n");//method to put a return into file.

		printf("type third keyword: ");
			fgets(book->wordT, maxWord, stdin);
			fixBuffer(book->wordT);
			fputs(book->wordT, fp);
			fprintf(fp, " ");//method to put a return into file.

		printf("\n\noutcome: ADDED ");
}//end makeBook.

/* function search a book 
   funzione cerca libro */
void search(struct cube *walk){

	char src[maxWord];
	int valWordF;
	int valWordS;
	int valWordT;
	int count = 0;

	printf("\ntype keyword: ");
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

/* function see library
   funzione guarda libreria */
void see(struct cube *walk, struct cube *head){
	
	int count = 0;

	walk = head;
	while(walk != NULL){
		printf("%d° | %s - %s - %s", count+1, walk->isbn, walk->title, walk->author);
		printf("\n--------------------------------------------------------------\n");
		
		count++;
		walk = walk->next;
	}// end while i.
}//end see.

/* function delete 
   funzione elimina */
void delete(struct cube *book, struct cube **head){
	
	struct cube *a;
	struct cube *b;
	char del[maxSpace];
	int valDel;

	printf("\ntype book title that you would delete: ");
	  fgets(del, maxSpace, stdin);
	  fixBuffer(del);

	  a = *head;
	  b = NULL;

	  while(a != NULL){
		valDel = strcmp(del, a->title);
		
		if(valDel == 0){
			
			if(a == *head){
				
				*head = a->next;
				free(a);

			}else{

				b->next = a->next;
				free(a);
			}//end if-else head.

		}//end if valDel.
		b = a;
		a = a->next;
	}//end while a.

	a = *head;
	while (a != NULL){
		printf("%s - %s - %s", a->isbn, a->title, a->author);
		a = a->next;
	}

}//end delete.