#include<stdio.h> 
#include<stdlib.h>

typedef struct Node{ 
    int key; 
    struct Node *left, *right; 
    int height; 
}Node; 
  
int height(Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
Node* newNode(int key) 
{ 
    Node* node = (Node*) malloc(sizeof(Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  

Node *rightRotate(Node *y) 
{ 
    Node *x = y->left; 
    Node *temp = x->right; 
  
    x->right = y; 
    y->left = temp; 
  
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 

    return x; 
} 
   
Node *leftRotate(Node *x) 
{ 
    Node *y = x->right; 
    Node *temp = y->left; 

    y->left = x; 
    x->right = temp; 

    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
 
    return y; 
} 
  
int getBalance(Node *N) { 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 

Node* insert(Node* node, int key) { 
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else 
        return node; 

    node->height = 1 + max(height(node->left), height(node->right)); 
                    
    int balance = getBalance(node); 
e 
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 

    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 

    if (balance > 1 && key > node->left->key) { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 

    if (balance < -1 && key < node->right->key) { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node; 
} 
void preOrder(Node *root) { 
    if(root != NULL) { 
        printf("%d ", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 

  
int main() { 
  Node *root = NULL; 
  int data,choice;
  while(1){
        printf("\nSelect one of the following:\n1. Insert\n2. Pre-Order Traversal\n3. Delete\n0. Exit\n\nYour Selection:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("\nEnter the number to be inserted: ");
                scanf("%d",&data);
                root = insert(root,data);
                break;
            case 2:
                printf("Preorder traversal of the constructed AVL tree is \n"); 
                preOrder(root);
                break;
            case 3:
                printf("\nEnter the number to be deleted: ");
                scanf("%d",&data);
                deleteNode(root,data);
                break;
            case 0:
                exit(1);
        }
    }
  
  /* root = insert(root, 10); 
  root = insert(root, 20); 
  root = insert(root, 30); 
  root = insert(root, 40); 
  root = insert(root, 50); 
  root = insert(root, 25);  */

  
  
  return 0; 
} 