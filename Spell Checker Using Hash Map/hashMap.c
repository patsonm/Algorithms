/*Name: Michael Patson
//File: hashMap.c
//Homework Assignment 5
//Due: june 4, 2018
//Implments hashmap
*/


#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
     assert(map != 0);

    //loop through array, creates a link
    //sould i make these NULL or 0, remember to test
     for (int i = 0; i < map->capacity; i++) {
          struct HashLink * currentLink = map->table[i];
          map->table[i] = 0;
         
          while (currentLink != 0) {

                struct HashLink * temp = currentLink;
                currentLink = currentLink->next;

                //create and delete within loop? add complex? no
                hashLinkDelete(temp);
          }
          free(map->table[i]);
     }
     free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != 0);

    int hashIndex = HASH_FUNCTION(key) % (map->capacity);

    struct HashLink *newNode = map->table[hashIndex];

    //checks for a match using string compare, keeps checking and if no match returns NULL
    while (newNode != 0) 
    {
        if (strcmp(newNode->key, key) == 0) 
        {
            return &(newNode->value);
        }
        else 
        {
            newNode = newNode->next;
        }
    }
    
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    //test what if set to NULL
    
    struct HashLink ** HT = map->table;
    
    int prevCap = map->capacity;
    
    hashMapInit(map, capacity);
    
    //copy
    for (int i = 0; i < prevCap; i++) 
    {
          struct HashLink * currentLink = HT[i];

          while (currentLink) 
          {
               hashMapPut(map, currentLink->key, currentLink->value);
               currentLink = currentLink->next;
          }
     }
    
    //delete old map
    for (int i = 0; i < prevCap; i++) 
    {
          struct HashLink * oldLink = HT[i];
          HT[i] = 0;

          while (oldLink != 0) {
               struct HashLink * temp = oldLink;
               oldLink = oldLink->next;
               hashLinkDelete(temp);
          }

          free(HT[i]);
     }

    free(HT);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    assert (map!=0);
    
    //just like with dynARR, check to see overload, double
    if (hashMapTableLoad(map) >= MAX_TABLE_LOAD) 
    {
        resizeTable(map, 2 * (map->capacity));
    }
    
    int hashIndex = HASH_FUNCTION(key) % (map->capacity);
    //get index location
    if (hashIndex < 0) 
    {
          hashIndex += map->capacity;
    }
    
    if (map->table[hashIndex] != 0) 
    {
          struct HashLink * curLink = map->table[hashIndex];
          
        
      //loops through and compares(should could use search function i guess)
      while (strcmp(curLink->key, key) != 0 && curLink->next != 0) 
      {
           curLink = curLink->next;
      }
      //not found, add new node
      if (curLink->next == 0 && strcmp(curLink->key, key) != 0) 
      {
           struct HashLink * addLink = hashLinkNew(key, value, map->table[hashIndex]);
           map->table[hashIndex] = addLink;
           map->size++;
      }
      //found
      else 
      {
           curLink->value = value;
      }
    }

     //bucket is emtpy, add node
     else 
     {
          struct HashLink * addLink = hashLinkNew(key, value, 0);
          map->table[hashIndex] = addLink;
          map->size++;
     }
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map!=0);
    assert(map->size>0);
    //maybe right a helper for this, use it a lot
    int hashIndex = HASH_FUNCTION(key) % map->capacity;
    
    struct HashLink * headLink;
    struct HashLink * curLink;
    struct HashLink * hashLink;
    
    curLink = map->table[hashIndex];
    headLink=curLink;
    hashLink=curLink;
    
    
    //loops through list until key is found
    
    while(curLink !=0)
    {
            if(strcmp(curLink->key,key)==0 && (curLink==headLink))
            {
                headLink=curLink->next;
                map->table[hashIndex]=headLink;

                hashLinkDelete(curLink);

                map->size--;
                curLink = 0;

            }
            else if (strcmp(curLink->key,key)==0 && (curLink!=headLink))
            {
                hashLink->next = curLink->next;
                hashLinkDelete(curLink);

                map->size--;
                curLink = 0;
            }
        else
        {
            hashLink=curLink;
            curLink=curLink->next;
        }
    }
    
    
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    assert (map!=0);
    
    int hashIndex = HASH_FUNCTION(key) % (map->capacity);

    struct HashLink * currentLink = map->table[hashIndex];
    //list is empty
    if(currentLink ==0)
    {
        return 0;
    }
    
    //list is not empty, look through list
    while (currentLink != 0) 
    {

        if (strcmp(currentLink->key, key) == 0)
        {
            return 1;
        }

        else 
        {
        currentLink = currentLink->next;
        }
    }
    
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    assert(map != 0);
    return(map->size);
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
        assert(map != 0);
        return(map->capacity);
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    assert(map!=0);
    //loop through to check
    int count = 0;
    int cap = map->capacity;
    
    for (int i = 0; i < cap; i++)
    {
          if (map->table[i] == 0) 
          {
               count++;
          }
     }

     return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    assert (map!=0);
    
    //cast float for integer math
    float buckets = (float)hashMapCapacity(map);
    float links = (float)hashMapSize(map);
    
    //ratio
    float load = links / buckets;

    return load;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}