#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Node
{
    int flight_number;
    /* char flight_name[20];
    int price;
    char time[10]; */
    char date[20];
    char from[20];
    char dst[20];

    struct Node *left, *right; 
    int height;
}Node;


Node* newNode(int key, char a[],char b[],char c[]) 
{ 
    Node* node = (Node*) malloc(sizeof(Node)); 
    node->flight_number   = key; 
    strcpy(node->date,a);
    strcpy(node->from,b);
    strcpy(node->dst,c);
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1; 

    return(node); 
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
  
int getBalance(Node *N) 
{ 
    if (N == NULL) 
        return 0; 

    return height(N->left) - height(N->right); 
} 

Node* insert(Node* node, int key, char a[],char b[],char c[]) 
{ 
    if (node == NULL) 
        return(newNode(key,a,b,c)); 
  
    if (key < node->flight_number) 
        node->left  = insert(node->left, key,a,b,c); 
    else if (key > node->flight_number) 
        node->right = insert(node->right, key, a,b,c); 
    else
        return node; 
  
    node->height = 1 + max(height(node->left), height(node->right)); 
    int balance = getBalance(node); 

    if (balance > 1 && key < node->left->flight_number) 
        return rightRotate(node); 

    if (balance < -1 && key > node->right->flight_number) 
        return leftRotate(node); 

    if (balance > 1 && key > node->left->flight_number) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 

    if (balance < -1 && key < node->right->flight_number) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node; 
} 

void preOrder(Node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->flight_number); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 

int main()
{
    int c, n;
    char date[20], from[20], to[20];
    Node *root;
    //root = new = (node*) malloc(sizeof(node));
    root = NULL;

    int flight_number;

    printf ("1. Add Flight Data \n2. Book Flights \n3. Exit\n");
    scanf ("%d", &c); 
    
    switch (c)
    {
        case 1: printf ("Enter number of flights to be added : ");
                scanf ("%d", &n);

                for (int i = 0; i < n; i++)
                {
                    printf ("1");
                    printf ("Enter flight number : ");
                    scanf ("%d", &flight_number);
                    printf ("Enter date : ");
                    scanf ("%s", date);
                    printf ("Enter departure city : ");
                    scanf ("%s", from);
                    printf ("Enter Arrival city : ");
                    scanf ("%s", to);

                    root = insert (root, flight_number, date, from, to);
                }
                printf ("\npreorder : ");
                preOrder (root);
    }
    return 0;
}