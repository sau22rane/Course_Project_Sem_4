#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

typedef struct Node{ 
    int key; 
    struct Node *left, *right; 
    int height;
    char date[20],from[20],dst[20]; 
}Node; 

typedef struct LinkedListNode{
    Node *ptr;
    struct LinkedListNode *next;
} LinkedListNode;
  

int max(int a, int b); 
int height(Node *N);
Node* newNode(int,char a[],char b[],char c[]);
Node *rightRotate(Node *y);
int getBalance(Node *N);
Node *leftRotate(Node *x) ;
Node* insert(Node* node, int key, char a[],char b[],char c[]);
void preOrder(Node *root);
Node * minValueNode(Node* node);
Node* deleteNode(Node* root, int key) ;
void search(Node *root, char a[], char b[], char c[]) ;
void add(Node *root);
LinkedListNode *head=NULL;

void search(Node *root, char a[], char b[], char c[]) { 
    if(root != NULL) { 
        if(strcmp(root->date,a)==0){
            add(root);
        }
        search(root->left,a,b,c); 
        search(root->right,a,b,c); 
    } 
} 

void add(Node *root){
    if(head == NULL){
        head = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        head->ptr = root;
        head-> next = NULL;
    }
    else{
        LinkedListNode *temp;
        temp = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        temp->ptr = root;
        temp-> next = head;
        head = temp;
    }
}

void display(){
    LinkedListNode *temp = head;
    while(temp){
        printf("%d %s %s %s\n",temp->ptr->key,temp->ptr->date,temp->ptr->from,temp->ptr->dst);
        temp = temp->next;
    }
}
  
int main() { 
  Node *root = NULL; 
  char date[20],from[20],dst[20];
  int data,choice;
  while(1){
        printf("\nSelect one of the following:\n1. Insert\n2. Pre-Order Traversal\n3. Delete\n0. Exit\n\nYour Selection:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("\nEnter the number to be inserted: ");
                scanf("%d",&data);
                scanf("%*c%[^\n]",date);
                scanf("%*c%[^\n]",from);
                scanf("%*c%[^\n]",dst);
                root = insert(root,data,date,from,dst);
                break;
            case 2:
                printf("Preorder traversal of the constructed AVL tree is \n"); 
                scanf("%*c%[^\n]",date);
                search(root,date,from,dst);
                display();
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
  return 0; 
} 































Node* newNode(int key, char a[],char b[],char c[]) 
{ 
    Node* node = (Node*) malloc(sizeof(Node)); 
    node->key   = key; 
    strcpy(node->date,a);
    strcpy(node->from,b);
    strcpy(node->dst,c);
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  
    return(node); 
} 

Node *rightRotate(Node *y) 
{ 
    Node *x = y->left; 
    Node *temp = x->right; 
  

    x->right = y; 
    y->left = temp; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
Node *leftRotate(Node *x) 
{ 
    Node *y = x->right; 
    Node *temp = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = temp; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(Node *N) { 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
Node* insert(Node* node, int key, char a[],char b[],char c[]) { 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(key,a,b,c)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key,a,b,c); 
    else if (key > node->key) 
        node->right = insert(node->right, key, a,b,c); 
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->key) { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->key) { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
void preOrder(Node *root) { 
    if(root != NULL) { 
        printf("%d %s", root->key, root->date); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 
Node * minValueNode(Node* node) 
{ 
    Node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

Node* deleteNode(Node* root, int key) 
{ 
    // STEP 1: PERFORM STANDARD BST DELETE 
  
    if (root == NULL) 
        return root; 
  
    // If the key to be deleted is smaller than the 
    // root's key, then it lies in left subtree 
    if ( key < root->key ) 
        root->left = deleteNode(root->left, key); 
  
    // If the key to be deleted is greater than the 
    // root's key, then it lies in right subtree 
    else if( key > root->key ) 
        root->right = deleteNode(root->right, key); 
  
    // if key is same as root's key, then This is 
    // the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            struct Node *temp = root->left ? root->left : 
                                             root->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
             *root = *temp; // Copy the contents of 
                            // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            struct Node* temp = minValueNode(root->right); 
  
            // Copy the inorder successor's data to this node 
            root->key = temp->key; 
  
            // Delete the inorder successor 
            root->right = deleteNode(root->right, temp->key); 
        } 
    } 
  
    // If the tree had only one node then return 
    if (root == NULL) 
      return root; 
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    int balance = getBalance(root); 
  
    // If this node becomes unbalanced, then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0) 
    { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root; 
} 


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




