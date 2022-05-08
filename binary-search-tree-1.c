/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */		// LVR
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */	// VLR
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */	// LRV
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
int isLeaf(Node* n);


int IsInitialized(Node* h);
int Scanf(int* k);


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- [정준호]    [2020069046] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			// scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)		// LVR
{
	if (ptr)
	{
		inorderTraversal(ptr->left);
		printf("%d ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)		// VLR
{
	if (ptr)
	{
		printf("%d ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)		// LRV
{
	if (ptr)
	{
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("%d ", ptr->key);
	}
}


// 이게 왜 가능한거지 ?
int insert(Node* head, int key)
{
	if (IsInitialized(head)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	Node* temp = searchIterative(head, key);
	Node* newNode;

	if (temp || !(head->left)) {
		newNode = (Node*) malloc(sizeof(Node));
		newNode->key = key;
		newNode->left = newNode->right = NULL;

		if (head->left)
			if (key < temp->key) temp->left = newNode;
			else if (temp->key < key) temp->right = newNode;
			else
				// 기존 노드의 내용을 갱신하는 코드 (ex: temp->data = data)
				printf("Updated the existing node.\n");
		else head->left = newNode;
	}

	return 0;
}


int deleteLeafNode(Node* head, int key)
{
	Node* temp = searchRecursive(head, key);

	if (temp->key == key) {
		if ((temp->left == NULL) && (temp->right == NULL)) {
			
		}
		else {
			printf("Found the node, but it is not a leaf.\n");
			return 1;
		}
	}
	else {
		printf("Couldn't find the node.\n");
	}
}


Node* searchRecursive(Node* ptr, int key)
{
	static Node* prev = NULL;

	if (!ptr) {
		printf("Couldn't find a corresponding node.");
		return prev;
	}
	if (key == ptr->key) {
		printf("Found the corresponding node.\n");
		return ptr;
	}
	if (key < ptr->key) {
		prev = ptr;
		return searchRecursive(ptr->left, key);
	}
	else {
		prev = ptr;
		return searchRecursive(ptr->right, key);
	}
}


Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;
	Node* prev = NULL;

	while (ptr)
	{
		if (key == ptr->key) {
			printf("Found the corresponding node.\n");
			return ptr;
		}
		if (key < ptr->key) {
			prev = ptr;
			ptr = ptr->left;
		}
		else {
			prev = ptr;
			ptr = ptr->right;
		}
	}
	printf("Couldn't find a corresponding node.");
	return prev;
}


/**
 * @brief Deallocates all the nodes including root pointer
 * 			before	the program terminates
 * 				or	proceeding initialization
 * 
 * @param head 
 * @return int 
 * 			successful	 	=> 0
 * 			unsuccessful	=> 1	
 */
int freeBST(Node* head)
{
	
}


/*-------------- 개인 정의 함수 --------------*/

/* initialize 안하고 insert나 delete의 command를 입력하면 Segmentation fault.
	각 기능을 수행하기 전에 initialized 됐는지 확인하는 전처리용 함수. */
int IsInitialized(Node* h) {
	if (h == NULL) return 1;
	else return 0;
}

/* main의 scanf("%d", &key)를 대체하는 함수. key에 정수를 입력 받는다 */
 /* 기존에서는 'Your key = '에 정수가 아닌 문자 등 다른 값을 입력하면
 	다음 프로그램 진행에 장애가 생긴다. 정수가 아닌 값을 입력 받으면 insert, delete 등
	수행을 하지 않고 버퍼를 비우도록 하여 문제를 해결하였다. */
int Scanf(int* k) {
	if (scanf("%d", k) == 1) {			// 제대로 정수를 입력 받으면 scanf의 반환값은 1(읽은 항목의 개수)
		while (getchar() != '\n');
		return 0;
	}
	else {
		printf("Not appropriate input. Input must be an integer. Try again.\n");
		while (getchar() != '\n');
		return 1;
	}
}
