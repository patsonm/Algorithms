/* CS261- Assignment 3 Linked List*/
/* Name: Michael Patson
 * Date: April 22
 * Solution description: Linked list assignment
 */

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) 
{
	assert(list != NULL);
    list->size=0;
    
    struct Link * front = malloc(sizeof(struct Link));
    list->frontSentinel=front;
    
    struct Link * back = malloc(sizeof(struct Link));
    list->backSentinel=back;
    
    front->value = 0;
    front->next = list->backSentinel;
    front->prev = NULL;
    
    back->value = 0;
    back->next = NULL;
    back->prev = list->frontSentinel;
    
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
    assert(link != 0);
    
    //create and set val
    struct Link * newLink = malloc(sizeof(struct Link));
    newLink->value = value;
    
    //set temp to previous(think like swap function wiht one extra step)
   
    
    newLink->value = value;
	newLink->prev = link->prev;
	newLink->next = link;
	link->prev->next = newLink;
	link->prev = newLink;
    
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != NULL);
    assert(link != NULL);
    
    
    //go to previous link next and tell it to point to next... skipping this link essentially
    link->prev->next = link->next;
    //
    link->next->prev= link->prev;
    list->size--;
    free(link);
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
    
    addLinkBefore(list, list->frontSentinel->next, value);
  
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
    
    addLinkBefore(list, list->backSentinel, value);	
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    assert(list != NULL);
    assert(list->size !=0);
	return(list->frontSentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    assert(list != NULL);
    assert(list->size !=0);
	return(list->backSentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != NULL);
    assert(list->size !=0);
  
    removeLink(list, list->frontSentinel->next);
    
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != NULL);
    assert(list->size !=0);
  
    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	if(list->size == 0)
        return 1;
    else
        return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list != NULL);
    
    struct Link *printLink = list->frontSentinel->next;
    
    while(printLink != list->backSentinel)
    {
		printf("%d\n", printLink->value);
		printLink = printLink->next;
	}
    
}

/**
 * Adds a link with the given value to the bag.
// Just add to front? already wrote method 

 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
    linkedListAddFront(list, value);
    
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 
Just checks for first instance
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
    assert(list->size !=0);
   
    struct Link *printLink = list->frontSentinel->next;
    
   while(printLink != list->backSentinel) 
   {
		if (printLink->value == value) 
        {
			return 1;
		}
		printLink = printLink->next;
	}
	return 0;
    
     
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
    assert(list->size !=0);
   
    struct Link *printLink = list->frontSentinel->next;
    
    while (printLink != list->backSentinel) 
    {
		if (printLink->value == value) 
        {
			printLink->prev->next = printLink->next;
			printLink->next->prev = printLink->prev;
			free(printLink);
			list->size--;
			break;
		}
		printLink = printLink->next;
    }
}
