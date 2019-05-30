/* CS261- Assignment 2 - stackapp*/
/* Name: Michael Patson
 * Date: April 16th, 2018
 * Solution description: Checks to see if (){}[] are balanced, using the technique discuessed in class
 */

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
    //repeat string(checking)
	printf("The String Input is: %s\n", s);
    
    assert(s !=0);

    char c = nextChar(s);
    char top;

    DynArr* str = newDynArr(10);
    //using the methods defined in the lectures(right bracket first)
    while(c != '\0')
    {
        if(!isEmptyDynArr(str))
            {
                top = topDynArr(str);
            }

    	if(c == '(' || c == '[' || c =='{')
            {
                pushDynArr(str, c);
            }

        if(c == ')' && top == '(')
            {
                if(isEmptyDynArr(str))
                {
                    return 0;
                }
                popDynArr(str);
            }

        if(c == ']' && top == '[')
            {
                if(isEmptyDynArr(str))
                {
                    return 0;
                }
                popDynArr(str);
            }


        if(c == '}' && top == '{')
            {
                if(isEmptyDynArr(str))
                {
                    return 0;
                }
                popDynArr(str);
            }


    	c = nextChar(s);

    }


    if(isEmptyDynArr(str))
    {
        deleteDynArr(str);
        str = 0;
        return 1;
    }
    else
    {
        deleteDynArr(str);
        str = 0;
        return 0;
    }

}


int main(int argc, char* argv[]){
	
	char* s=argv[1];
    //char* s = "{(4 + (3 * 2 - 5)}";
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

