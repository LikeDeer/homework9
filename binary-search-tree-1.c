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
void postorderTraversal_freeBST(Node* ptr);

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
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);

			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
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
		inorderTraversal(ptr->left);	// L
		printf("%d ", ptr->key);		// V
		inorderTraversal(ptr->right);	// R
	}
}

void preorderTraversal(Node* ptr)		// VLR
{
	if (ptr)
	{
		printf("%d ", ptr->key);		// V
		preorderTraversal(ptr->left);	// L
		preorderTraversal(ptr->right);	// R
	}
}

void postorderTraversal(Node* ptr)		// LRV
{
	if (ptr)
	{
		postorderTraversal(ptr->left);	// L
		postorderTraversal(ptr->right);	// R
		printf("%d ", ptr->key);		// V
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
	if (IsInitialized(head)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	Node* temp = searchRecursive(head->left, key);		// delete에서는 Recursive로 호출해보자

	if (temp->key == key) {			// key를 가진 노드를 발견 했는데,
		if ((temp->left == NULL) && (temp->right == NULL)) {	// leaf 이면,
			free(temp);							// 삭제

			temp = searchIterative(head->left, key);	// 그 부모 노드의 링크를 null로 초기화
			if (temp->key < key) temp->left = NULL;
			else temp->right = NULL;
		}
		else {						// leaf 가 아니면,
			printf("Found the node but it was not a leaf.\n");
			return 1;
		}		
	}
	else
		printf("Couldn't find the node.\n");

	return 0;
}


Node* searchRecursive(Node* ptr, int key)
{
	static Node* prev = NULL;		// 탐색을 실패하면 NULL을 반환하지 않고
									//   마지막 탐색 대상 노드인 prev를 반환
	if (!ptr) {
		return prev;
	}
	if (key == ptr->key) {
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
	Node* prev = NULL;			// 탐색을 실패하면 NULL을 반환하지 않고
								//   마지막 탐색 대상 노드인 prev를 반환
	while (ptr)
	{
		if (key == ptr->key) {
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
	if (IsInitialized(head))
		return 1;

	postorderTraversal_freeBST(head->left);
	free(head);
	printf("Good Bye\n");

	return 0;
}


/*-------------- 개인 정의 함수 --------------*/

/* 모든 노드를 순회하는 함수 중 하나를 수정해서 freeBST를 구현. */
 /* 어떤 함수든, 노드들을 한 번씩만 방문하기 때문에 가능하다. */
void postorderTraversal_freeBST(Node* ptr)		// LRV
{
	if (ptr)
	{
		postorderTraversal_freeBST(ptr->left);
		postorderTraversal_freeBST(ptr->right);
		printf("%d ", ptr->key);
		free(ptr);
	}
}


/* initialize 안하고 insert나 delete의 command를 입력하면 Segmentation fault.
	각 기능을 수행하기 전에 initialized 됐는지 확인하는 전처리용 함수. */
int IsInitialized(Node* h) {
	if (h == NULL) return 1;
	else return 0;
}
