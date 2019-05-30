/* CS261- Assignment 1 - Q.4*/
/* Name: Michael Patson
 * Date: April 7
 * Solution description:Write a function void camelCase(char* word) where word consists of more than two words separated by underscore such as “random_word” or
"this_is_my_first_programming_assignment". camelCase() should remove underscores from the sentence and rewrite in lower camel case” (https://
en.wikipedia.org/wiki/Camel_case). Watch out for the end of the string, which is denoted by ‘\0’. You have to ensure that legal strings are given to the
camelCase() function.
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

int lengthWord(char* word){
    //a simple counter looking for the string termination
    int length = 0;
    for(int x = 0; word[x] != '\0'; x++)
    {
        length++;
    }
    return length;
}


/*is string valid, exits if it is not*/
void validString(char* word){
//calls function to check length
    int size=lengthWord(word);
    
 for (int x = 0; word[x] != '\0'; x++)
    {
     if (word[x] >= 'A' && word[x] <= 'Z'){
         printf("Character is Upper Case Letters: %c \n",word[x]);
         printf("Invalid Input: Program will now exit \n");
         exit(EXIT_SUCCESS);
     }
     //else
        //printf("Character is Not Upper Case Letters:%c \n",word[x]);
     
 }
}

void camelCase(char* word){
     /*Convert to camelCase*/
    
    int i, k;
    
    int size = lengthWord(word);
    //first look for _ and then slide letters over
    for (i = 0; i < size; ++i){
        if(word[i]== '_')
        {
            word[i] = toUpperCase(word[i+1]);
         //now slide the values over
            for(k = i + 1; k < size -1; k++)
            {
                word[k]=word[k+1];
                word[k+1]='\0';
            }
        size--;
    
        }
    
    }
}


int main(){
 /*Read the string from the keyboard */
    char s[500];
      
    
    printf("\nEnter The Character : ");
    scanf("%s", s); 
    
    validString(s);
    
    /*Call camelCase*/
    camelCase(s);
    
    /*Print the new the string */
    printf("%s\n", s);
    
    return 0;
    
}
