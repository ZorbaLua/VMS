#ifndef LINKEDLIST_H
#define LINKEDLIST_H


typedef struct node {
    struct node* next;
    struct node* prev;
    void* data; 
} Node, *LinkedList;



int  LinkedList_remove(LinkedList, void**);
int  LinkedList_next(LinkedList);
int  LinkedList_prev(LinkedList);
void LinkedList_add(LinkedList, void*);


#endif
