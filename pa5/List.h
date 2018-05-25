// Michelle Ly
// mly8
// pa5

// This is a header file for List.c

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
// Returns reference to new empty List object. 
List newList(void);
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);

// Access functions -----------------------------------------------------------
// Returns the length of L.
int length(List L);
// Returns the index of cursor.
int index(List L);
// Returns the value at the front of L.
int front(List L);
// Returns the value at the back of L.
int back(List L);
// Returns the value of cursor.
int get(List L);
// Returns true (1) if A is identical to B, false (0) otherwise.
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------
// Resets this List to its original empty state.
void clear(List L);
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L);
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L);
// If cursor is defined and not at front, moves cursor one step toward
// front of this List.
void movePrev(List L);
// If cursor is defined and not at back, moves cursor one step toward
// back of this List.
void moveNext(List L);
// Places new data element at the front of L.
void prepend(List L, int data);
// Places new data element at the end of L.
void append(List L, int data);
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data);
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data);
// Deletes element at front of L.
void deleteFront(List L);
// Deletes element at back of L.
void deleteBack(List L);
// Deletes cursor element.
void delete(List L);

// Other Functions ------------------------------------------------------------
// Prints the List.
void printList(FILE* out, List L);
// Returns a new List representing the same integer sequence as this List.
List copyList(List L);

#endif