#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

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

int delete_number;
typedef struct LinkedListNode
{
    Node *ptr;
    int index;
    struct LinkedListNode *next;
} LinkedListNode;

LinkedListNode *head=NULL;

char *strupr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = toupper((unsigned char)*p);
      p++;
  }

  return str;
}

void strip(char *s)
{
	int  i,j;
 
	for(i=0;s[i]==' '||s[i]=='\t';i++);
		
	for(j=0;s[i];i++)
	{
		s[j++]=s[i];
	}
	s[j]='\0';
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]!=' '&& s[i]!='\t')
				j=i;
	}
	s[j+1]='\0';
}

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
        head->index = 1;
    }

    else
    {
        LinkedListNode *temp, *new;
        new = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        new -> ptr = root;
        new -> next = NULL;
        temp = head;
        while (temp->next != NULL)   
            temp = temp->next;     
        new->index = (temp->index)+1;
        temp->next = new;
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

int display(struct LinkedListNode* head)
{
    int ret;

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
            /* printf("----------------------------------------------------------------\n"); */
			printf("#%d\t\t%d\t\t %s\t\t %s\t\t %s\t\t %s\t\t %s\t\t Rs.%d\t\t \n", temp->index, temp->ptr->flight_number, temp->ptr->flight_name, temp->ptr->date, temp->ptr->time, temp->ptr->from, temp->ptr->dst, temp->ptr->price );
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
			temp=temp->next;
		}
		printf("#%d\t\t%d\t\t %s\t\t %s\t\t %s\t\t %s\t\t %s\t\t Rs.%d\t\t \n", temp->index, temp->ptr->flight_number, temp->ptr->flight_name, temp->ptr->date, temp->ptr->time, temp->ptr->from, temp->ptr->dst, temp->ptr->price );
        
        printf ("\nEnter the serial number of the flight you want to book : ");
        scanf ("%d", &ret);
	}

    return (ret);
}

int book(struct LinkedListNode* head, int no)
{
    char cust_name[20], gender[50], file_name[20];
    int cust_mob, age, n, OTP;
    LinkedListNode *temp;
    temp = head;
    int amount;

    printf ("\nEnter number of tickets you want to book : ");
    scanf ("%d", &n);

    printf ("\nEnter the name of the file to save your tickets into : ");
    scanf ("%s", file_name);
    strcat (file_name, ".txt");

    FILE *fp;
    fp = fopen(file_name, "w+");

    for (int i=0; i<n; i++)
    {
        printf ("\nEnter passenger no. %d name : ", (i+1));
        scanf ("%s", cust_name);
        printf ("Enter passenger no. %s's age : ", cust_name);
        scanf ("%d", &age);
        printf ("Enter passenger no. %s's gender: ", cust_name);
        scanf ("%s", gender);
        printf ("Enter passenger no. %s's mobile number : ", cust_name);
        scanf ("%d", &cust_mob); 

        while (temp -> index != no)
            temp = temp->next;

        fprintf (fp, "Passenger Name : %s\n", cust_name);
        fprintf (fp, "Passenger age  : %d\n", age);
        fprintf (fp, "Passenger gender : %s\n", gender);
        fprintf (fp, "Passenger mobile number : %d\n", cust_mob);
        fprintf (fp, "\nBooked Flight Information : \n\n");
        fprintf (fp, "%d\t\t %s\t\t %s\t\t %s\t\t %s\t\t %s\t\t Rs.%d\t\t \n", temp->ptr->flight_number, temp->ptr->flight_name, temp->ptr->date, temp->ptr->time, temp->ptr->from, temp->ptr->dst, temp->ptr->price);

        fprintf(fp, "----------------------------------------------------------------------------------------------------------------------------------\n");
    } 
 
    amount = n * temp->ptr->price;
    printf ("\nTotal payable amount = %d\n", amount);
    
    for(int i = 1; i<=3; i++)
    {
        printf ("\nEnter the OTP after making the payment : ");
        scanf ("%d", &OTP);

        if (OTP == 1234)
        {
            fclose (fp);
            printf ("\nYour tickets have been booked and saved to local disk. Thank You!\n\n");
            return 0;
        }

        else if (OTP != 1234 && i == 3)
        {
            fclose (fp);
            fp = fopen(file_name, "w");
            fprintf (fp, " ");
            fclose (fp);
            printf ("\nSorry we couldn't book your tickets as you have entered the wrong OTP, please try booking again\n\n");
            return 0;
        }

        else
        {
            printf ("Wrong OTP! You have more %d chances.\n", (3-i));
        }
    }                    
}

void update(Node *root, int flight_number)
{
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

    if(found)
    {
        printf("\nUpdating data of flight number : %d and flight name : %s\n",flight_number, root->flight_name);
        
        while(1)
        {
            printf("\nSelect the field which has to be updated\n1. Price: %d\n2. Time: %s\n3. Date: %s\n4. Departue city: %s\n5. Arrival city: %s\n0. Done Updating\n\nYour Selection: ", root->price, root->time, root->date, root->from, root->dst);
            scanf("%d",&choice);
            
            switch(choice)
            {
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

    else
    {
        printf("Flight to be Updated not found!!\n\n");
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
        
        if( (root->left == NULL) || (root->right == NULL) )  
        {  
            printf("Record by flight number %d deleted\n\n",delete_number);
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

void write (Node *root)
{
    FILE *fp = fopen ("flight data.csv", "a");

    if(root != NULL) 
    { 
        write(root->left); 
        fprintf (fp, "%d,%s,%s,%s,%s,%s,%d\n", root->flight_number, root->flight_name, root->from,root->dst, root->date, root->time, root->price);
        write(root->right); 
    }

    fclose (fp);
}

int main()
{
    int c, n;
    char date[20], from[20], to[20], flight_name[20], time[20];
    Node *root;
    root = NULL;
    int no;

    FILE *fp;

    int flight_number = 0, price;
    int j =1, field_count;

    while(j>0)
    {
        printf ("1. Add Flight Data \n2. Book Flights \n3. Update \n4. Delete flight \n5. Exit\n");
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
                        root = insert (root, flight_number, date, from, to, flight_name, time, price);
                    }

                    /* while (!feof(fp))
                    {
                    fscanf (fp, "%d %s %s %s %s %s %d", &flight_number, flight_name, from, to, date, time, &price);
                    root = insert (root, flight_number, date, from, to, flight_name, time, price);
                    } */
                    
                    printf ("\nFile Read and Flight data successfully added\n\n");

                    /* printf ("\npreorder : ");
                    preOrder (root); */

                    fclose (fp);
                    break;

            case 2: printf ("\nEnter departure city : ");
                    scanf ("%[^\n]%*c", from);
                    strip(from);
                    strcpy(from,strupr(from));

                    printf ("Enter Arrival city : ");
                    scanf ("%[^\n]%*c", to);
                    strip(to);
                    strcpy(to,strupr(to));
                    printf ("Enter date : ");
                    scanf ("%s", date);
                    printf("\n");

                    search (root, date, from, to);
                    no = display(head);
                    book (head, no);

                    head = NULL;
                    
                    break;

            case 3: printf ("\nEnter flight number whose data you want to update : ");
                    scanf ("%d", &flight_number);

                    update (root, flight_number);                  
                    
                    break;

            case 4: printf ("\nEnter flight number to delete : ");
                    scanf ("%d", &flight_number);
                    delete_number = flight_number;
                    deleteNode(root, flight_number);
                    
                    break;

            case 5: { }
                    FILE *fp = fopen ("flight data.csv", "w+");
                    fclose (fp);
                    write (root);

                    return 0;
        }
    }
}
