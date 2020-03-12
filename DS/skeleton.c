#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct node
{
    /* int flight_number;
    char flight_name[20];
    int price;
    char time[10]; */
    char date[20];
    char from[20];
    char to[20];

    struct node *left, *right; 
    int height;
}node;

typedef struct list
{
    struct node* data;
    struct list* next;
}list;

//functions for insert 

list* search (char from[20], char to[20], char date[20], node *root)\
{

}

void display (list *l)
{

}

int main()
{

}