
#include "linkedList.h"

#include <stdlib.h>


int LinkedList_remove(LinkedList ll, void** ret){
    if(ll == NULL) return -1;
    *ret = ll->data;
    if(ll->prev != NULL){
        ll = ll->prev;
        (*ll).next = ll->next->next;
        if((*ll).next != NULL) ((*(ll->next)).prev) = ll;
    }
    else if(ll->next != NULL){
        ll = ll->next;
        (*ll).prev = NULL;
    }
    return 0;
}

int LinkedList_next(LinkedList ll){
    if(ll == NULL) return -1;
    if(ll->prev == NULL) return 1; //e o ultimo
    ll = ll->next;

    return 0;
}

int LinkedList_prev(LinkedList ll){
    if(ll == NULL) return -1;
    if(ll->prev == NULL) return 1; //e o primeiro
    ll = ll->prev;
    return 0;
}

void LinkedList_add(LinkedList ll, void* data){
    Node* newnode = (Node*)malloc(sizeof(struct node));
    (*newnode).data = data;
    if(ll == NULL){
        (*newnode).next = NULL;
        (*newnode).prev = NULL;
        ll = newnode;
        return;
    }
    if(ll->prev != NULL) (*(ll->prev)).next = newnode;
    if(ll->next != NULL) (*(ll->next)).prev = newnode;
    (*newnode).prev = ll->prev;
    (*newnode).next = ll->next;
    ll = newnode;
}
