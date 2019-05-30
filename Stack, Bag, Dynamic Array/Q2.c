/* CS261- Assignment 1 - Q.2*/
/* Name: Michael Patson
 * Date: April 7
 * Solution description: A simple program to test knowledge of pointers
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /* Increment a */
    *a+=1;
    /* Decrement  b */
    *b-=1;
    /* Assign a+b to c */
    c = *a + *b;
    /* Return c */
    return c;
}

int main(){
    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x, y, z;
    
    x=((rand() % 10) + 1);
    y=((rand() % 10) + 1);
    z=((rand() % 10) + 1);
    
    /* Print the values of x, y and z */
    printf("x: %d\n", x);
    printf("y: %d\n", y);
    printf("z: %d\n", z);
    /* Call foo() appropriately, passing x,y,z as parameters */
    
    int result = foo(&x, &y, 0);
    
     /* Print the value returned by foo */
    printf("Int return value of foo: %d\n", result);
    
    /* Print the values of x, y and z */
    printf("x: %d y: %d z: %d\n", x, y, z);
    
    
    return 0;
}
    
    

