/* Doubly Linked List implementation */
#include<stdio.h>
#include<stdlib.h>

struct Node  {
	int data;
	struct Node* next;
	struct Node* prev;
};

struct Node* head; // global variable - pointer to head node.

//Creates a new Node and returns pointer to it. 
struct Node* GetNewNode(int x) {
	struct Node* newNode
		= (struct Node*)malloc(sizeof(struct Node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(int x) {
	struct Node* newNode = GetNewNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head; 
	head = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(int x) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(x);
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}

//Prints all the elements in linked list in forward traversal order
void Print() {
	struct Node* temp = head;
	printf("Forward: ");
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

//Prints all elements in linked list in reverse traversal order. 
void ReversePrint() {
	struct Node* temp = head;
	if(temp == NULL) return; // empty list, exit
	// Going to last Node
	while(temp->next != NULL) {
		temp = temp->next;
	}
	// Traversing backward using prev pointer
	printf("Reverse: ");
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->prev;
	}
	printf("\n");
}

int test1() {
	/*Driver code to test the implementation*/
	head = NULL; // empty list. set head as NULL. 
	
	printf("Test1...\n");
	// Calling an Insert and printing list both in forward as well as reverse direction. 
	InsertAtHead(6); Print(); ReversePrint();
	InsertAtTail(2); Print(); ReversePrint();
	InsertAtTail(4); Print(); ReversePrint();
	InsertAtTail(8); Print(); ReversePrint();
	printf("done test1.\n");
}

int test2() {
	/*Driver code to test the implementation*/
	head = NULL; // empty list. set head as NULL. 
	
	printf("Test2...\n");
	// Calling an Insert and printing list both in forward as well as reverse direction. 
	InsertAtHead(2); Print(); ReversePrint();
	InsertAtTail(4); Print(); ReversePrint();
	InsertAtTail(6); Print(); ReversePrint();
	InsertAtTail(8); Print(); ReversePrint();
	printf("done test2.\n");
}

int main() {
	test1();	
	test2();
}