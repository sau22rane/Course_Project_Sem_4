#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Node
{
    int flight_number;
    char flight_name[20];
    int price;
    char time[10];
    char date[20];
    char from[20];
    char dst[20];

    struct Node *left, *right; 
    int height;
}Node;

typedef struct LinkedListNode
{
    Node *ptr;
    struct LinkedListNode *next;
} LinkedListNode;

LinkedListNode *head=NULL;

Node* newNode(int key, char a[],char b[],char c[], char d[], char e[], int f) 
{ 
    Node* node = (Node*) malloc(sizeof(Node)); 
    node->flight_number  = key; 
    node->price = f;
    strcpy(node->date,a);
    strcpy(node->from,b);
    strcpy(node->dst,c);
    strcpy(node->flight_name,d);
    strcpy(node->time,e);
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

Node* insert(Node* node, int key, char a[],char b[],char c[], char d[], char e[], int f)
{ 
    if (node == NULL) 
        return(newNode(key,a,b,c,d,e,f)); 
  
    if (key < node->flight_number) 
        node->left  = insert(node->left, key,a,b,c,d,e,f); 
    else if (key > node->flight_number) 
        node->right = insert(node->right, key, a,b,c,d,e,f); 
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

void add(Node* root)
{
    if(head == NULL)
    {
        head = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        head->ptr = root;
        head-> next = NULL;
    }

    else
    {
        LinkedListNode *temp;
        temp = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        temp->ptr = root;
        temp-> next = head;
        head = temp;
    }
}

void search(Node *root, char a[], char b[], char c[]) 
{
    if(root != NULL) 
    { 
        if(strcmp(root->date,a)==0 && strcmp(root->from,b)==0 && strcmp(root->dst,c)==0)
        {
            add(root);
        }
        search(root->left,a,b,c); 
        search(root->right,a,b,c); 
    } 
} 

void display(struct LinkedListNode* head)
{
	struct LinkedListNode *temp;
	temp=head;

	if(head==NULL)
	{
		printf("No flights\n");
	}

	else
	{
		while(temp->next!=NULL)
		{
			printf("%d\t %s\t %s\t %s\t %s\t %s\t %d\t \n", temp->ptr->flight_number, temp->ptr->flight_name, temp->ptr->date, temp->ptr->time, temp->ptr->from, temp->ptr->dst, temp->ptr->price );
            printf("----------------------------------------------------------------\n");
			temp=temp->next;
		}
		printf("%d\t %s\t %s\t %s\t %s\t %s\t %d\t \n\n", temp->ptr->flight_number, temp->ptr->flight_name, temp->ptr->date, temp->ptr->time, temp->ptr->from, temp->ptr->dst, temp->ptr->price );
	}
}

int main()
{
    int c, n;
    char date[20], from[20], to[20], flight_name[20], time[20];
    Node *root;
    root = NULL;

    int flight_number, price;
    int j =1;

    while(j>0)
    {
        printf ("1. Add Flight Data \n2. Book Flights \n3. Exit\n");
        printf ("your choice : ");
        scanf ("%d", &c); 

        switch (c)
        {
            case 1: printf ("Enter number of flights to be added : ");
                    scanf ("%d", &n);

                    for (int i = 0; i < n; i++)
                    {
                        printf ("Enter flight number : ");
                        scanf ("%d", &flight_number);
                        printf ("Enter flight name : ");
                        scanf ("%s", flight_name);
                        printf ("Enter date : ");
                        scanf ("%s", date);
                        printf ("Enter time : ");
                        scanf ("%s", time);
                        printf ("Enter departure city : ");
                        scanf ("%s", from);
                        printf ("Enter Arrival city : ");
                        scanf ("%s", to);
                        printf ("Enter price : ");
                        scanf ("%d", &price);
                        printf("----------------------------------------------------------------\n");

                        root = insert (root, flight_number, date, from, to, flight_name, time, price);
                    }
                    /* printf ("\npreorder : ");
                    preOrder (root); */

                    break;

            case 2: printf ("Enter departure city : ");
                    scanf ("%s", from);
                    printf ("Enter Arrival city : ");
                    scanf ("%s", to);
                    printf ("Enter date : ");
                    scanf ("%s", date);

                    search (root, date, from, to);
                    display(head);
                    break;

            case 3 : return 0;
        }
    }
}