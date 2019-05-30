/* CS261- Assignment 1 - Q.0*/
/* Name: Michael Patson
 * Date: April 7
 * Solution description: A simple program to test knowledge of pointers
 */
 

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value of iptr*/
     printf("The value pointed to by iptr is: %d\n",*iptr);
     /*Print the address pointed to by iptr*/
     printf("The address pointed to by iptr is: %p\n", &(*iptr));
     /*Print the address of iptr itself*/
     printf("The address of iptr itself is: %p\n", &iptr);
     /*Change the value of iptr itself*/
     *iptr = 100;
}

int main(){
    
    /*declare an integer x and initialize it randomly to a value in [0,10] */
    int x = 1 + (rand() % 10);
    
    /*print value of x*/
    printf("The value of int x is: %d\n",x);
    
    /*Print the address of x*/
    printf("The address of x is: %p\n", (void*) &x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*Print the value of x*/
    printf("The value of x is: %d\n",x);
   
    /*Answer the question */
    /* Yes, the value of "x" is different.  The last line in fooA, is dereferencing iptr which points to x and assigns it a new value of 100 */
    
    return 0;
   
    
}


