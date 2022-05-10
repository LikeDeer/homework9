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
			// if(ptr != NULL)
			if (ptr->key == key)
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


int insert(Node* head, int key)
{
	if (IsInitialized(head)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	Node* temp = searchIterative(head, key);		// 부모가 될 노드 위치

	if (head->left) {	// 공백 트리가 아니면,
		if (temp->key > key) temp->left = newNode;
		else if (temp->key < key) temp->right = newNode;
		else {		/* key를 가진 기존 노드가 있다면, 업데이트하는 코드를 실행하고 삽입은 안함. */ 
			// 기존 노드의 내용을 갱신하는 코드 (ex: temp->data = data)
			printf("Updated the existing node.\n");
		}
	}
	else				// 공백 트리 였다면, 첫 노드로 삽입
		head->left = newNode;

	return 0;
}


int deleteLeafNode(Node* head, int key)
{
	/* 전처리 */
	if (IsInitialized(head)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	
	if (head->left == NULL) {
		printf("Nothing to delete.\n");
		return 1;
	}


	Node* ptr = head->left;
	Node* prev = head;				// prev는 삭제하기 전 부모 노드

	while(ptr) {

		if(ptr->key == key) {		// key를 가진 노드를 찾았는데,
			if(ptr->left == NULL && ptr->right == NULL) {		// leaf 노드 이면, 삭제
				
				if(prev == head)		// 첫 노드가 leaf 였다면, 삭제 후 공백 트리
					head->left = NULL;

				// 부모 노드 링크 NULL로 초기화
				if(prev->left == ptr)
					prev->left = NULL;
				else
					prev->right = NULL;

				free(ptr);

				return 0;
			}
			else {					// leaf 노드가 아니면 아무것도 안하기
				printf("Found the node but it was not a leaf");
			}
			return 0;
		}

		// key를 가진 노드를 발견하지 못하면 다음 노드를 확인하기
		prev = ptr;				// prev는 ptr을 따라가기

		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	printf("There's no key node.\n");

	return 1;
}


/* 탐색에 성공하면, 그 노드를 반환. 실패하면 NULL을 반환 */
Node* searchRecursive(Node* ptr, int key)
{
	if (!ptr) {
		printf("Couldn't find it.\n");
		return NULL;
	}

	if (key == ptr->key) {
		return ptr;
	}
	else if (key < ptr->key) {
		return searchRecursive(ptr->left, key);
	}
	else {
		return searchRecursive(ptr->right, key);
	}
}


/* 이 함수로 insert 에서 부모가 될 노드의 위치를 찾을 것이다.
	searchRecursive 와 달리 탐색의 마지막 노드를 반환하도록 한다.
	즉, 탐색에 실패했을 때, NULL을 반환하지 않고, 이전 탐색 노드를 반환한다. */
Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;
	Node* prev = head;			// 탐색 실패 했을 때, prev를 반환한다.

	while (ptr)
	{
		if (key == ptr->key) {
			return ptr;
		}
		if (key < ptr->key) {
			prev = ptr;				// 다음 노드를 탐색할 때, prev는 ptr을 따라감.
			ptr = ptr->left;
		}
		else {
			prev = ptr;
			ptr = ptr->right;
		}
	}

	printf("Couldn't find the node.\n");
	return prev;
}


int freeBST(Node* head)
{
	if (IsInitialized(head))
		return 1;

	printf("Freeing\n");
	postorderTraversal_freeBST(head->left);		// 개인 정의 함수 참고.
	free(head);
	printf("\n");

	return 0;
}


/*-------------- 개인 정의 함수 --------------*/

/* 모든 노드를 순회하는 함수 중 LRV를 수정해서 freeBST를 구현. */
void postorderTraversal_freeBST(Node* ptr)		// LRV
{
	if (ptr)
	{
		postorderTraversal_freeBST(ptr->left);
		postorderTraversal_freeBST(ptr->right);
		printf("%d ", ptr->key);
		free(ptr);					// V (본 노드 방문) 시 free
	}
}


/* initialize 안하고 insert나 delete의 command를 입력하면 Segmentation fault.
	각 기능을 수행하기 전에 initialized 됐는지 확인하는 전처리용 함수. */
int IsInitialized(Node* h) {
	if (h == NULL) return 1;
	else return 0;
}
