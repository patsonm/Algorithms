/* CS261- Assignment 1 - Q.1*/
/* Name: Michael Patson
 * Date: April 7
 * Solution description: A simple student class that creates UNIQUE student ID and random test scores
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

/*Set a constant for number of students, to be used for loops and memory allocation*/

const int Num_Student = 10;

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* students = malloc(sizeof(struct student)*Num_Student);
     /*return the pointer*/
    return students;
}

void swap (int *a, int *b){
    /*Swaps two integers, to be used in array to mix student IDs*/
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomizer ( int arr[])
{
  //Changes the seed value
    srand ( time(NULL) );
 
    //move the elements around
    for (int i=9; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    int ID[Num_Student];
    for (int m=0; m < Num_Student; m++)
        ID[m]=m+1;
    randomizer(ID);    
    for(int i = 0; i < Num_Student; i++){
        students[i].id = ID[i];
        students[i].score = ((rand() % 100) + 1);
    }

}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    printf("== STUDENTS ==\n");
    printf("ID SCORE\n");
    for(int i = 0; i < Num_Student; i++)
    {
        printf("%d %d\n", students[i].id, students[i].score);
    }
    //Print a new line to end list for readability
    printf("\n");
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = 101;
    int max = (-1);
    float total = 0;
    float average;
    
    //calculate min and max and total
    for(int i = 0; i < Num_Student; i++)
    {
        //min
        if(students[i].score < min || min == 101)
            min=students[i].score;
        
        //max    
        if(students[i].score > max || max == -1)
            max=students[i].score;
    total = total + students[i].score;
    }

    //print statemnts
    printf("==SCORES ==\n");
    printf("Minimum: %d\n",min);
    printf("Maximum: %d\n",max);
    printf("Average: %f\n", total/Num_Student);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    if (stud != 0) 
    {
        free(stud);
    }
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);    
    
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
