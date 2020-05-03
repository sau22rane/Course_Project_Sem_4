#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int result_no, iter;
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


void search(Node *root, int flight_number) 
{
    iter++;
    if(root != NULL) 
    {   
        if(flight_number>root->flight_number)
            search(root->right,flight_number);
        else if(flight_number<root->flight_number)
            search(root->left,flight_number);
        else 
        {
            printf("Flight name: %s\nDeparture city: %s\nArival city: %s\nDate: %s\nTime: %s\nAmount: %d\n",root->flight_name,root->from,root->dst,root->date,root->time,root->price);
        }
    } 
} 



Node * minValueNode(Node* node)  
{  
    Node* current = node;  
    
    while (current->left != NULL)  
        current = current->left;  
    
    return current;
}  





Node* bst_insert(Node* node, int key, char a[],char b[],char c[], char d[], char e[], int f)
{ 
    if (node == NULL) 
        return(newNode(key,a,b,c,d,e,f)); 
  
    if (key < node->flight_number) 
        node->left  = bst_insert(node->left, key,a,b,c,d,e,f); 
    else if (key > node->flight_number) 
        node->right = bst_insert(node->right, key, a,b,c,d,e,f); 
    else
        return node;
}


int height_tree(Node* node)  
{ 
   if (node==NULL)  
       return 0; 
   else 
   { 
       /* compute the depth of each subtree */
       int lDepth = height_tree(node->left); 
       int rDepth = height_tree(node->right); 
  
       /* use the larger one */
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}

int main()
{
    int c, n;
    char date[20], from[20], to[20], flight_name[20], time[20];
    Node *avl_root, *bst_root;
    avl_root = NULL;
    bst_root = NULL;
    int no;

    FILE *fp;

    int flight_number = 0, price;
    int j =1, field_count;

    while(j>0)
    {
        printf ("1. Add Flight Data \n2. Get Info \n3. Exit\n");
        printf ("Your choice : ");
        scanf ("%d", &c); 
        scanf("%*c");

        switch (c)
        {
            case 1: fp = fopen ("flight data.csv", "r+");
                    char buffer[1024];

                    if(!fp)
                    {
                        printf("Can't open file\n");
                    }

                    while (fgets (buffer, 1024, fp))
                    {
                        field_count = 0;
                        char *field = strtok (buffer, ",");

                        while (field)
                        {
                            if (field_count == 0)
                                flight_number = atoi(field);
                            if (field_count == 1)
                                strcpy (flight_name,field);
                            if (field_count == 2)
                                strcpy (from, field);
                            if (field_count == 3)
                                strcpy (to, field);
                            if (field_count == 4)
                                strcpy (date, field);
                            if (field_count == 5)
                                strcpy (time, field);
                            if (field_count == 6)
                                price = atoi(field); 

                            field = strtok (NULL, ",");
                            field_count++;
                        }
                        avl_root = insert (avl_root, flight_number, date, from, to, flight_name, time, price);
                        bst_root = bst_insert (bst_root, flight_number, date, from, to, flight_name, time, price);
                        
                    }

                    /* while (!feof(fp))
                    {
                    fscanf (fp, "%d %s %s %s %s %s %d", &flight_number, flight_name, from, to, date, time, &price);
                    root = insert (root, flight_number, date, from, to, flight_name, time, price);
                    } */
                    
                    printf ("\nFile Read and Flight data successfully added\n\n");
                    int avl_height = height_tree(avl_root);
                    int bst_height = height_tree(bst_root);
                    printf("AVL tree created with height of %d \n",avl_height);
                    printf("BST created with height of %d \n\n",bst_height);

                    /* printf ("\npreorder : ");
                    preOrder (root); */

                    fclose (fp);
                    break;

            case 2: printf("Enter flight number to get information: ");
                    scanf("%d",&flight_number);
                    printf("\nUSING AVL TREE\n");
                    search (avl_root, flight_number);
                    printf("No. of nodes visited %d .\n\n",iter);
                    iter = 0;
                    printf("USING BST\n");
                    search (bst_root, flight_number);
                    printf("No. of nodes visited %d .\n\n",iter);
                    
                    
                    break;

            case 3:
                    return 0;
        }
    }
}