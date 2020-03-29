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
            printf("----------------------------------------------------------------\n");
			printf("%d\t %s\t %s\t %s\t %s\t %s\t %d\t \n", temp->ptr->flight_number, temp->ptr->flight_name, temp->ptr->date, temp->ptr->time, temp->ptr->from, temp->ptr->dst, temp->ptr->price );
            printf("----------------------------------------------------------------\n");
			temp=temp->next;
		}
		printf("%d\t %s\t %s\t %s\t %s\t %s\t %d\t \n\n", temp->ptr->flight_number, temp->ptr->flight_name, temp->ptr->date, temp->ptr->time, temp->ptr->from, temp->ptr->dst, temp->ptr->price );
        printf("----------------------------------------------------------------\n");
	}
}

void update(Node *root, int flight_number){
    int found =0, choice;
    while(root != NULL) 
    { 
        if(root->flight_number<flight_number)
        {
            root = root->right;
            continue;
        }
        if(root->flight_number>flight_number)
        {
            root = root->left;
            continue;
        }
        if(root->flight_number == flight_number)
        {
            found = 1;
            break;
        }
    } 
    if(found){
        printf("\nUpdating data of flight number %d: %s\n",flight_number,root->flight_name);
        while(1){
            printf("Select the field which has to be updated\n1. Price: %d\n2. Time: %s\n3. Date: %s\n4. Departue city: %s\n5. Arrival city: %s\n0. Done Updating\nYour Selection: ", root->price, root->time, root->date, root->from, root->dst);
            scanf("%d",&choice);
            switch(choice){
                case 1: printf("Enter the new price: ");
                        scanf("%d",&root->price);
                        break;
                case 2: printf("Enter the new time of departure: ");
                        scanf("%s",root->time);
                        break;
                case 3: printf("Enter the new date of departure: ");
                        scanf("%s",root->date);
                        break;
                case 4: printf("Enter the new departure city: ");
                        scanf("%s",root->from);
                        break;
                case 5: printf("Enter the new arrival city: ");
                        scanf("%s",root->dst);
                        break;
                case 0: return ;
            }
        }
    }
    else{
        printf("Flight to be Updated not found!!\n");
        return;
    }
}

Node * minValueNode(Node* node)  
{  
    Node* current = node;  
    while (current->left != NULL)  
        current = current->left;  
    return current;
}  


Node* deleteNode(Node* root, int flight_number)  
{  
      
    if (root == NULL)  
    {
        printf("\nNo flight record by that number exits\n");
        return root;
    }
    if ( flight_number < root->flight_number )  
        root->left = deleteNode(root->left, flight_number);
    else if( flight_number > root->flight_number )  
        root->right = deleteNode(root->right, flight_number);  
  
    else
    {  
        printf("\nRecord by flight number %d deleted\n",flight_number);
        if( (root->left == NULL) || (root->right == NULL) )  
        {  
            Node *temp = root->left ? root->left : root->right; 
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else 
            *root = *temp;

            free(temp);  
        }  
        else
        {   
            Node* temp = minValueNode(root->right);  
            root->flight_number = temp->flight_number;  
            root->right = deleteNode(root->right, temp->flight_number);  
        }  
    }  

    if (root == NULL)  
    return root;  
    root->height = 1 + max(height(root->left), height(root->right));  
    int balance = getBalance(root);  
  
    if (balance > 1 && getBalance(root->left) >= 0)  
        return rightRotate(root);  
   
    if (balance > 1 && getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  

    if (balance < -1 && getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    if (balance < -1 && getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
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
        printf ("1. Add Flight Data \n2. Book Flights \n3. Update\n4. Delete a recoed\n5. Exit\n");
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
                    head = NULL;
                    break;

            case 3: printf ("Enter flight number : ");
                    scanf ("%d", &flight_number);
                    update(root, flight_number);
                    break;
            
            case 4:printf ("Enter flight number to delete : ");
                    scanf ("%d", &flight_number);
                    deleteNode(root, flight_number);
                    break;

            case 5 : return 0;
        }
    }
}




