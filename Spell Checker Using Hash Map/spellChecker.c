/*Name: Michael Patson
//File: main.c
//Homework Assignment 5
//Due: june 4, 2018
//Spellchecker program
*/

#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_FUNCTION hashFunction1


/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
     // FIXME: implement
    
    //aready lowercase
    char * key = nextWord(file);
    while (key != NULL) 
    {
        hashMapPut(map, key, 1);
        free(key);
        key = nextWord(file);
    }
}

//distance calc posted on Piazza forum
//https://www.lemoda.net/c/levenshtein/

int LevDistance (const char * word1, const char * word2)
{
    int len1 = strlen (word1);
    int len2 = strlen (word2);
    int matrix[len1 + 1][len2 + 1];
    int i;
        for (i = 0; i <= len1; i++) 
        {
            matrix[i][0] = i;
        }
        for (i = 0; i <= len2; i++) 
        {
            matrix[0][i] = i;
        }
    for (i = 1; i <= len1; i++) 
    {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    char lowerBuffer[256];
    
   for (int j = 0; j<=256; j++)
   {
      lowerBuffer[j] = '\0';
        inputBuffer[j] = '\0';
   }
    int quit = 0;
    while (!quit)
     {
          /* Prompt user for word */
          printf("Enter a word or \"quit\" to quit: ");
          /* Read in word */
          scanf("%s", inputBuffer);
        int z=0;
        //changes cap
        while(inputBuffer[z] ) 
        {
            lowerBuffer[z]=(tolower(inputBuffer[z]));
            z++;
        }

          // Implement the spell checker code here..
          /* Check if user chose to quit */
          if (strcmp(inputBuffer, "quit") == 0)
          {
               quit = 1;
          }
          //check
          else {
               //correct word
              while(inputBuffer[z] ) 
        {
            lowerBuffer[z]=(tolower(inputBuffer[z]));
            z++;
        }
               if (hashMapContainsKey(map, lowerBuffer)) {
                    printf("The inputted word, %s,  is spelled correctly.\n", inputBuffer);
               }
               //incorrect word, 
               else {
                    //creates an array for suggestions
                    char * suggestedWords[5];
                    //hw suggests 5
                        for (int i = 0; i < 5; i++) 
                        {
                             suggestedWords[i] = '\0';
                        }
                    //find where word should be inserted, used for finding nearby
                    int hashIndex = HASH_FUNCTION(lowerBuffer);
                
                    int distance = -1;//initial distance, want to increase to find closest
                    int close = 1;  //from documentation https://www.lemoda.net/c/levenshtein/
                   
                    //remember on test links need new structs... consfusing with array
                    struct HashLink * curLink = map->table[hashIndex];
                    
                    int count = 0;
                    int suggestedIndex = 0;

                    while (hashIndex < map->capacity && count <= 5)
                    {
                        
                         //copied from hast map search, while not at end
                         while (curLink != 0) {
                              //give lowercase to avoid capital letter error
                              distance = LevDistance(lowerBuffer, curLink->key);
                             
                              if (distance > 0 && distance <= close) {
                                   //before giving word, check to see if in array. 
                                   int duplicate = 0;
                                   for (int i = 0; i <= 5; i++) {
                                        if (suggestedWords[i] == curLink->key)
                                        {
                                             duplicate = 1;
                                        }
                                   }
                                   
                                 if (!duplicate) {
                                        //add word to suggested word array (5)
                                        suggestedWords[suggestedIndex] = curLink->key;
                                        suggestedIndex++;

                                        if (count <= 5) 
                                        {
                                             count++;
                                        }
                                        
                                        if (suggestedIndex > 5) 
                                        {
                                             suggestedIndex = 0;
                                        }
                                   }
                              }
                              
                              curLink = curLink->next;
                              distance = -1; //variable from function reset to -1
                         }

                         hashIndex++;
                         //expand error range
                         if (hashIndex >= map->capacity && count <= 5) {
                              hashIndex = 0;
                              close++;
                         }
                         
                         curLink = map->table[hashIndex];
                    
                
                    }

                    /* Print suggestions */
                   printf("You entered: %s.\n", lowerBuffer);
                    printf("Did you mean...\n");
                    for (int i = 0; i < 5; i++) {
                              printf("%s\n", suggestedWords[i]);
                    }
                   
                   for (int j = 0; j<=256; j++)
                   {
                      lowerBuffer[j] = '\0';
                        inputBuffer[j] = '\0';
                   }
               }
          }
     }

     hashMapDelete(map);
     return 0;
}