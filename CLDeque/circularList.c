/* CS261- Assignment 3 Linked List*/
/* Name: Michael Patson
 * Date: April 22
 * Solution description: Circular Linked list assignment
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
    struct Link * link = malloc(sizeof(struct Link));
    link->next=link;
    link->prev=link;
    
    list->size=0;
    list->sentinel = link;
    
    
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link * link = malloc(sizeof(struct Link));
    link->next=NULL;
    link->prev=NULL;
    
    link->value=value;
    
    
    return link;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 
 //didnt update previous... should still be the same
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link * newLink = createLink(value);
    newLink->prev = link;
	newLink->next = link->next;
    
	link->next->prev = newLink;
	link->next = newLink;
	
    list->size++;
              
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	struct Link *printLink = list->sentinel;
    
    while (printLink->next != link) {
		printLink = printLink->next;
	}
	
    printLink->next = link->next;
	
    free(link);
	
    list->size--;

}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while(!circularListIsEmpty(list)) {
	   circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
    addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
    assert(list!=NULL);
    return (list->sentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list!=NULL);
    return (list->sentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list!=NULL);
    removeLink(list,list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    assert(list!=NULL);
    removeLink(list,list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != NULL);
    
    if (list->size ==0)
        return 1;
    else
        return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{

	assert(list != NULL);
    
    struct Link *printLink = list->sentinel->next;
    
    for(int i =0; i < list->size; i++)
    {
        printf("%g \n", printLink->value);
		printLink = printLink->next;
    }
   
    
    /*while(printLink != list->sentinel)
    {
		printf("%g \n", printLink->value);
		printLink = printLink->next;
	}
    */
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	//think like swap function, swapping pointers
    
   assert(list != NULL);
    
    struct Link *printLink = list->sentinel->next;
    struct Link *nextLink; //=malloc(sizeof(struct Link));
    struct Link *prevLink; //=malloc(sizeof(struct Link));
    
    
    for (int x = 0; x < list->size; x++)
    {
        nextLink = printLink->next;
		printLink->next = prevLink;
		prevLink = printLink;
		printLink = nextLink;
    }
        list->sentinel->next = prevLink;
    
   
    /*
      
        while(printLink != list->sentinel)
    {
		tmp->value=printLink->value;
		tmp->prev = printLink->next;
        tmp->next = printLink->prev;
        printLink=tmp;
        printLink = printLink->next;
	}
    */
}
