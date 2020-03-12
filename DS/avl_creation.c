#include<stdio.h> 
#include<stdlib.h>

typedef struct Node{ 
    int key; 
    struct Node *left, *right; 
    int height; 
}Node; 
  
// A utility function to get maximum of two integers 
int max(int a, int b); 
  
// A utility function to get the height of the tree 
int height(Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
Node* newNode(int key) 
{ 
    Node* node = (Node*) 
                        malloc(sizeof(Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
Node *rightRotate(Node *y) 
{ 
    Node *x = y->left; 
    Node *temp = x->right; 
  
    // Perform rotation 
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
Node* insert(Node* node, int key) { 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
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
        printf("%d ", root->key); 
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