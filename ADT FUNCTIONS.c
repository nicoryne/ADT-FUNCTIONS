#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct studentInfo{
	char name[50];
	int age;
	int classID;
}Person;

typedef struct node {
	Person student;
	struct node *link;
}Node;

Node* createNode(Person data);
void displayNodes(Node** head);
Person addPerson(char name[50], int age, int classID);

void insertFront(Node** head, Person student);
void insertRear(Node** head, Person student);
void insertClassID(Node** head, Person student);
void insertInto(Node **head, Person student, int pos);
void deleteFront(Node** head);
void deleteRear(Node** head);
void deleteClassID(Node** head, int classID);
void deleteInto(Node **head, int pos);
int main(){
	Node *head = (Node*)malloc(sizeof(Node));
	
	head->student = addPerson("Johnny", 18, 1);
	head->link = NULL;
	
	insertRear(&head, addPerson("Ryan",19,2));
	insertFront(&head, addPerson("Liam",17,4));
	insertClassID(&head, addPerson("Justin",16,3));
	insertClassID(&head, addPerson("Tristan",18,2));

	displayNodes(&head);		
}

Node* createNode(Person data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	if (newNode == NULL) {
		printf("Memory allocation failed!");
		exit(1);
	}
	
	newNode->student = data;
	newNode->link = NULL;
	return newNode;
}
void displayNodes(Node **head) {
	int i = 0;
	Node* current = *head;
	while(current!=NULL){
		printf("STUDENT[%d]\t\nName: [%1s]\nAge: [%1d]\nClass ID: [%1d]\n\n",
		i+1,
		current->student.name, 
		current->student.age, 
		current->student.classID);
		
		current = current->link;
		i++;
	}
}

Person addPerson(char name[50], int age, int classID) {
	Person inputPerson;
	
	inputPerson.age = age;
	inputPerson.classID = classID;
	strcpy(inputPerson.name, name);
	
	return inputPerson;
}

void insertRear(Node** head, Person student) {
	Node* newNode = createNode(student);
	
	if (*head == NULL) {
		*head = newNode; 
	} else {
		Node* current = *head;
		
		while (current->link != NULL) {
			current = current->link;
		}
		
		current->link = newNode;
	}
}

void insertFront(Node** head, Person student) {
	Node* newNode = createNode(student);
	
	if(*head == NULL) {
		*head = newNode;
	} else {
		newNode->link = *head;
		*head = newNode;
	}
}

void insertClassID(Node** head, Person student) {
	Node* newNode = createNode(student);
	
	if(*head == NULL) {
		*head = newNode;
	} else {
		Node* current = *head;
		
		while (current->link != NULL && current->student.classID > newNode->student.classID) {
			current = current->link;
		}
		
		newNode->link = current->link;
		current->link = newNode;
	}
}

void insertInto(Node **head, Person student, int pos) {
	int i;
	Node* newNode = createNode(student);
	
	if(*head == NULL) {
		*head = newNode;
	} else {
		Node *current = *head;
		
		for(i = 0; current->link != NULL && i < pos - 1; i++) {
			current = current->link;
		}
		
		newNode->link = current->link;
		current->link = newNode;
	}
}


void deleteFront(Node** head) {
	if(*head == NULL) {
		printf("Linked List is empty.\n");
		return;
	}
	
	Node* temp = *head;
	*head = (*head)->link;
	free(temp);
}

void deleteRear(Node** head) {
	if(*head == NULL) {
		printf("Linked List is empty.\n");
		return;
	} 
	
	Node* current = *head;
	
	while(current->link->link != NULL) {
		current = current->link;
	}
	
	free(current->link);
	current->link = NULL;
}

void deleteClassID(Node **head, int classID){
	if(*head == NULL) {
		printf("Linked list is empty.\n");
		return;
	}
	
	Node* current = *head;
	
	while(current->link != NULL && current->link->student.classID != classID) {
		current = current->link;
	}
	
	free(current->link);
	current->link = current->link->link;
}

void deleteInto(Node **head, int pos){
	int i;
	
	if(*head == NULL) {
		printf("Linked list is empty.\n");
		return;
	}
	
	Node* current = *head;
	Node* prev;
	for(i = 0; current->link != NULL && i < pos; i++) {
		prev = current;
		current = current->link;
		
	}
	
	prev->link = current->link;
}
