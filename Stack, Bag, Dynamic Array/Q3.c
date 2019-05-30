/* CS261- Assignment 1 - Q.3*/
/* Name: Michael Patson
 * Date: April 7
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


struct student{
	int id;
	int score;
};

struct student* allocate(int n){
     /*Allocate memory for ten students*/
     struct student* students = malloc(sizeof(struct student) * n);
     /*return the pointer*/
    return students;
}

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
   struct student swap;

   for (int i = 0; i < (n - 1); i++) {
      for (int k = 0; k < n - i - 1; k++) {
         if (students[k].score > students[k+1].score) {
            swap = students[k];
            students[k] = students[k+1];
            students[k+1] = swap;
         }
      }
   }     
}


void swap (int *a, int *b){
    /*Swaps two integers, to be used in array to mix student IDs*/
    int temp = *a;
    *a = *b;
    *b = temp;
}


void randomizer ( int arr[], int n){
    //move the elements around
    for (int i=n; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
        //printf("These are swapped %d, %d\n:", arr[i], arr[j]);
    }
}

void generate(struct student* students, int n){
     /*Generate random and unique ID and scores for ten students, ID being between number student and 0 scores between 0 and 100*/
   int ID[n];
    for (int m=0; m < n; m++)
    {ID[m]=m+1;
    }
    randomizer(ID, n); 
   
    
    for(int i = 0; i < n; i++){
        students[i].id = ID[i];
        students[i].score = ((rand() % 100) + 1);
    }

}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    if (stud != 0) 
    {
        free(stud);
    }
}

void output(struct student* students, int n){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    printf("== STUDENTS ==\n");
    printf("ID SCORE\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d %d\n", students[i].id, students[i].score);
    }
    //Print a new line to end list for readability
    printf("\n");
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 20;
    
    
    struct student* stud = NULL;
    
    /*Allocate memory for n students using malloc.*/
   stud = allocate(n);
    
    /*Generate random and unique IDs and random scores for the n students, using rand().*/
    //used swap function for unique ids from Q1
    
    
    /*call generate*/
    generate(stud, n);
    
    /*Print the contents of the array of n students.*/
    printf("==Before Sorting==\n");
    /*call output*/
    output(stud, n);

    /*Pass this array along with n to the sort() function*/
    sort(stud,n);
    
    /*Print the contents of the array of n students.*/
    printf("==After Sorting==\n");
    output(stud, n);
    
    deallocate(stud);
    return 0;
}
