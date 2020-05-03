#ifndef BACKEND_H
#define BACKEND_H
#endif // BACKEND_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

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
    int index;
    struct LinkedListNode *next;
}LinkedListNode;
LinkedListNode *head = NULL;
void preOrder(Node *);
int book(struct LinkedListNode *, int);
void update(Node *, int);
Node * minValueNode(Node *);
Node* deleteNode(Node *, int);
void write (Node *);


