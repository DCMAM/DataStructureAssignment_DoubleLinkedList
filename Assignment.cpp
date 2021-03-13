/*
 *	created : April 3rd 2020
 *	by		: David Christian M. A. M. (2301932172)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tnode{
	char movie[24];
	int rating;
	struct tnode *next;
	struct tnode *prev;
}*head = NULL, *tail = NULL;

int total = 0;
int flag_1 = 0;

void pushTail(char n[], int rating){
	struct tnode *curr = (struct tnode *)malloc(sizeof(struct tnode));
	strcpy(curr->movie, n);
	curr->rating = rating;
	curr->next = NULL;
	if(head == NULL){
		head = tail = curr;
		head->prev = NULL;
	}
	else{
		tail->next = curr;
		curr->prev = tail;
		tail = curr;
	}
	total++;
}

void Delete(char n[]){
	struct tnode *curr = head;
	struct tnode *temp = (struct tnode *)malloc(sizeof(struct tnode));
	if(head != NULL){
		// jika n ada di head
		if(strcmp(head->movie, n) == 0){
			head = head->next;
			free(curr);
		}
		// jika n ada di tail
		else if(strcmp(tail->movie, n) == 0){
			while(curr->next != tail){
				curr = curr->next;
			}
//			curr = tail->prev;
			free(tail);
			tail = curr;
			tail->next = NULL;	
		}
		// jika n ada di antara head dan tail
		else {
			while(strcmp(curr->next->movie, n) > 0){
				curr = curr->next;
			}
			temp = curr->next;
			free(temp);
			curr->next = temp->next;
		}
	}
	total--;
}

void viewLinkedList(){
	struct tnode *curr = head;
	while(curr){ // curr != NULL
		printf("| %-20s %d\n", curr->movie, curr->rating);;
		curr = curr->next;
	}
}

void sort_list_rating(){
    struct tnode *ptr1, *ptr2;
    int temp;
    ptr1 = head;
    while(ptr1 -> next != NULL){
    	ptr2 = ptr1 -> next;
        while(ptr2 != NULL){
            if(ptr1->rating > ptr2->rating){
            	temp = ptr1->rating;
            	ptr1->rating = ptr2->rating;
            	ptr2->rating = temp;
            }
        	ptr2 = ptr2->next;
        }
    	ptr1 = ptr1->next;
    }
}

void sort_list_string(){
    struct tnode *ptr1, *ptr2;
    int temp;
    ptr1 = head;
    while(ptr1 -> next != NULL){
    	ptr2 = ptr1 -> next;
        while(ptr2 != NULL){
            if(strcmp(ptr1->movie, ptr2->movie) > 0){
				char t[10];
				strcpy(t, ptr1->movie);
				strcpy(ptr1->movie, ptr2->movie);
				strcpy(ptr2->movie, t);
			}
        	ptr2 = ptr2->next;
        }
    	ptr1 = ptr1->next;
    }
//	return start; // Had to be added
}

int thereIsMovie(char n[]){
	struct tnode *curr = head;
	if(head != NULL){
		// jika n ada di head
		if(strcmp(head->movie, n) == 0){
			return 1;
		}
		// jika n ada di tail
		else if(strcmp(tail->movie, n) == 0){
			return 1;	
		}
		// jika n ada di antara head dan tail
		else {
			while(curr->next != NULL){
				if(strcmp(curr->next->movie, n) == 0){
					return 1;
				}
				curr = curr->next;
			}
		}
	}
	return 0;
}

int main(){
	do{
		int menu = 0;
		printf(".. Cinema 20-1 ..\n\n");
		printf("1. View All Movies (by Name Ascending)\n");
		printf("2. View Movie by Rating\n");
		printf("3. Add New Movie\n");
		printf("4. Delete Movie\n");
		printf("5. Exit\n");
		printf(".. Choice : ");
		scanf("%d", &menu);
		
		if(menu == 1){
			if(total == 0){
				printf("| Movie Name           Rating\n");
				printf("| -                    -\n");				
				system("pause");
			}
			else{
				printf("| Movie Name           Rating\n");
				sort_list_string();
				viewLinkedList();
				system("pause");
			}
		}
		else if(menu == 2){
			if(total == 0){
				printf("| Movie Name           Rating\n");
				printf("| -                    -\n");				
				system("pause");
			}
			else{
				sort_list_rating();
				viewLinkedList();
				system("pause");
			}
		}
		else if(menu == 3){
			char movie[24];
			int rating;
			do{
				printf("MovieName [max 20 char] : ");
				scanf("%s", &movie);
			}while(strlen(movie) > 20);
			do{
				printf("Rating [1..10] : ");
				scanf("%d", &rating);
			}while(rating > 10 || rating < 1);
			pushTail(movie, rating);
			printf("\nSuccessfully add new movie!\n");
			system("pause");
		}
		else if(menu == 4){
			if(total == 0){
				printf("No Movie\n");		
				system("pause");	
			}
			else{
				printf("| Movie Name           Rating\n");
				char movie[24];
				int rating;
				viewLinkedList();
				do{
					printf("MovieName [max 20 char] : ");
					scanf("%s", &movie);
				}while( !(thereIsMovie(movie)));
				Delete(movie);
				printf("successfully delete %s!\n", movie);
				system("pause");
			}
		}
		else if(menu == 5){
			free(head);
			free(tail);
			break;
		}
		else{
			printf("You should input 1-7\n");
		}
		system("cls");
	}while(1);
	
	return 0;
}
