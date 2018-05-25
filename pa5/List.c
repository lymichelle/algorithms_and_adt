// Michelle Ly
// mly8
// pa5

// This is a doubly linked list ADT, used to store and manipulate data.

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Node and List Objects ------------------------------------------------------
typedef struct NodeObj{
        int data;
        struct NodeObj* next;   
        struct NodeObj* prev;
} NodeObj;
typedef NodeObj* Node;
typedef struct ListObj{
        Node front;
        Node back;
        Node cursor;
        int length;
        int index;
} ListObj;

typedef ListObj* List;
// Constructors-Destructors ---------------------------------------------------
Node newNode(int data){
        Node N = malloc(sizeof(NodeObj));
        N->data = data;
        N->next = NULL;
        return(N);
}

void freeNode(Node* pN){
        if( pN!=NULL && *pN!=NULL ){
                free(*pN);
                *pN = NULL;
        }
}
List newList(void){
        List L;
        L = malloc(sizeof(ListObj));
        L->front = L->back = NULL;
        L->length = 0;
        L->index = -1;
        L->cursor = NULL;
        return(L);
}
void freeList(List* pL){
        if(pL!=NULL && *pL!=NULL) { 
                while( (*pL)->length != 0 ) { 
                        deleteFront(*pL); 
                }
                free(*pL);
                *pL = NULL;
        }
}
// Access functions -----------------------------------------------------------
// Returns the number of elements in this List.
int length(List L){
        if( L==NULL ){
                printf("List Error: calling length() on NULL List reference\n");
                exit(1);
        }
        return L->length;
}
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1
int index(List L){
        if(L->cursor==NULL){
                return -1;
        }
        return L->index;
}
// Returns front element. Pre: length()>0
int front(List L){
        if( L==NULL ){
                printf("List Error: calling front() on NULL List reference\n");
                exit(1);
        }
        if( L->length == 0 ){
                printf("List Error: calling front() on an empty List\n");
                exit(1);
        }
        return L->front->data;
}
// Returns back element. Pre: length()>0
int back(List L){
        if( L==NULL ){
                printf("List Error: calling back() on NULL List reference\n");
                exit(1);
        }
        if( L->length == 0 ){
                printf("List Error: calling back() on an empty List\n");
                exit(1);
        }
        return L->back->data;
}
// Returns cursor element. Pre: length()>0, index()>=0
int get(List L){
        if( L->length == 0 ){
                printf("List Error: calling get() on an empty List\n");
                exit(1);
        }
        if( L->index < 0 ){
                printf("List Error: calling get() on an empty List\n");
                exit(1);
        }
        return L->cursor->data;
}
// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B){
        int eq = 0;
        Node N = NULL;
        Node M = NULL;
        if( A==NULL || B==NULL ){
                printf("List Error: calling equals() on NULL List reference\n");
                exit(1);
        }
        eq = ( A->length == B->length );
        N = A->front;
        M = B->front;
        while( eq && N!=NULL){
                eq = (N->data==M->data);
                N = N->next;
                M = M->next;
        }
        return eq;
}
// Manipulation procedures ----------------------------------------------------
// Resets this List to its original empty state.
void clear(List L){
        while(L->length != 0){
                deleteFront(L);
        }
}
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
        if(L->length > 0){
                L->cursor = L->front;
                L->index = 0;
        }
}
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
        if( L==NULL ){
                printf("List Error: calling moveBack() on NULL List reference\n");
                exit(1);
        }
        if(L->length > 0){
                L->cursor = L->back;
                L->index = L->length -1;
        }
}
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
        if( L==NULL ){
                printf("List Error: calling movePrev() on NULL List reference\n");
                exit(1);
        }
        if (L->index != -1 && L->cursor == L->front) {
                L->index = -1;
                L->cursor = NULL;
        }
        if (L->index != -1 && L->cursor != L->front) {
                L->cursor = L->cursor->prev;
                L->index--;
        }       
}
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
        if( L==NULL ){
                printf("List Error: calling moveNext() on NULL List reference\n");
                exit(1);
        }
        if (L->index != -1 && L->cursor == L->back) {
                L->index = -1;
                L->cursor = NULL;
        }
        if (L->index != -1 && L->cursor != L->back) {
                L->cursor = L->cursor->next;
                L->index++;
        }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
        if( L==NULL ){
                printf("List Error: calling prepend() on NULL List reference\n");
                exit(1);
        }
        Node N = newNode(data);
        if( L->length==0 ) { 
                L->front = L->back = N;
                L->front->prev = NULL;
                L->back->next = NULL;
        }else{ 
                L->front->prev = N; 
                N->next = L->front;
                L->front = N; 
        }
        L->length++;
}
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
        if( L==NULL ){
                printf("List Error: calling append() on NULL List reference\n");
                exit(1);
        }
        Node N = newNode(data);
        if( L->length==0 ) { 
                L->front = L->back = N; 
                L->front->prev = NULL;
                L->back->next = NULL;
        }else{ 
                L->back->next = N; 
                N->prev = L->back;
                L->back = N; 
        }
        L->length++;
}
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
        if( L==NULL ){
                printf("List Error: calling insertBefore() on NULL List reference\n");
                exit(1);
        }
        Node N = newNode(data);
        if( L->length == 0 ){
                printf("List Error: calling insertBefore() on an empty List\n");
                exit(1);
        }
        if( L->index < 0 ){
                printf("List Error: calling insertBefore() on an empty List\n");
                exit(1);
        }
        if(L->index==0){
                prepend(L, data);
        }
        else{
                N->next = L->cursor;
                N->prev = L->cursor->prev;
                L->cursor->prev->next = N;
                L->cursor->prev = N;
                L->length++;
        }
}
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
        if( L==NULL ){
                printf("List Error: calling insertAfter() on NULL List reference\n");
                exit(1);
        }
        Node N = newNode(data);
        if( L->length == 0 ){
                printf("List Error: calling insertAfter() on an empty List\n");
                exit(1);
        }
        if( L->index < 0 ){
                printf("List Error: calling insertAfter() on an empty List\n");
                exit(1);
        }
        if(L->index==L->length-1){
                append(L, data);
        }
        else{
                N->prev = L->cursor;
                N->next = L->cursor->next;
                L->cursor->next->prev = N;
                L->cursor->next = N;
                L->length++;
        }
}
// Deletes the front element. Pre: length()>0
void deleteFront(List L){
        Node N = NULL;
        if( L==NULL ){
                printf("List Error: calling deleteFront() on NULL List reference\n");
                exit(1);
        }
        if( L->length==0 ){
                printf("List Error: calling deleteFront() on an empty List\n");
                exit(1);
        }
        if(L->cursor==L->front){
                L->cursor==NULL;
        }
        N = L->front;
        if( L->length > 1 ) { 
                L->front = L->front->next; 
                L->front->prev = NULL;
        }else{ 
                L->front = L->back = NULL; 
        }
        L->length--;
        freeNode(&N);
}
// Deletes the back element. Pre: length()>0
void deleteBack(List L){
        Node N = NULL;
        if( L==NULL ){
                printf("List Error: calling deleteBack() on NULL List reference\n");
                exit(1);
        }
        if( L->length==0 ){
                printf("List Error: calling deleteBack() on an empty List\n");
                exit(1);
        }
        if(L->cursor==L->back){
                L->cursor==NULL;
        }
        N = L->back;
        if( L->length > 1 ) { 
                L->back = L->back->prev; 
                L->back->next = NULL;
        }else{ 
                L->back = L->front = NULL; 
        }
        L->length--;
        freeNode(&N);
}
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
        Node N = NULL;
        if( L==NULL ){
                printf("List Error: calling delete() on NULL List reference\n");
                exit(1);
        }
        if( L->length==0 ){
                printf("List Error: calling delete() on an empty List\n");
                exit(1);
        }
        N = L->cursor;
        if( L->cursor==front ){
                deleteFront(L);
                L->length--;
        }
        if( L->cursor==back ){
                deleteBack(L);
                L->length--;
        }
        L->cursor->next->prev = L->cursor->prev;
        L->cursor->prev->next = L->cursor->next;
        L->length--;
        freeNode(&N);
}
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
         Node N = NULL;
         if( L==NULL ){
                 printf("List Error: calling printList() on NULL List reference\n");
                 exit(1);
         }
         for(N = L->front; N != NULL; N = N->next){
                 fprintf(out, "%d ", N->data);
         }
         fprintf(out, "\n");
}
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
        if( L==NULL ){
                 printf("List Error: calling copyList() on NULL List reference\n");
                 exit(1);
         }
        List Li = newList();
        Node N = L->front;
        while (N != NULL) {
                append(Li, N->data);
                N = N->next;
        }
        return Li;
}