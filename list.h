/*
 ============================================================================
 Name        : list.c
 Author      : mahendra pratap singh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
   char  data[1000];
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//display the list
void printList() {
   struct node *ptr = head;


   //start from the beginning
   while(ptr != NULL) {
      printf("%s\n ",ptr->data);
      ptr = ptr->next;
   }


}


//insert link at the first location
void push(char data[1000]) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));


   strcpy(link->data,data);

   //point it to old first node
   link->next = head;

   //point first to new first node
   head = link;
}

//removes first item
struct node* popTop() {

   //save reference to first link
   struct node *tempLink = head;

   //mark next to first link as first
   head = head->next;

   //return the removesd link
   return tempLink;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   struct node *current;

   for(current = head; current != NULL; current = current->next) {
      length++;
   }

   return length;
}

//find a link with given key
struct node* find(char data[1000]) {

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(strcmp(current->data , data)) {   // return 0 on matching
	   puts(current->data);
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }

   //if data found, return the current Link
   return current;
}

//removes a link with given key
struct node* popKey(char data[1000]) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(strcmp(current->data ,data)) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }

   return current;
}




/*
void main() {
   push("RAM");
   printList();
   push("SHAM");
   printList();
   push("SITA");



   printf("Original List: ");

   //print list
   printList();

   while(!isEmpty()) {
      struct node *temp = removesFirst();
      printf("\nremovesd value:");
      printf("%s\n ",temp->data);
   }
   printList();

   printf("\nList after deleting all items: ");
   printList();


   return;






}*/
