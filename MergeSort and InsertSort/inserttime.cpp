/********************************
/* Michael Patson
/* Oregon State
/* HW Assignment 1
/* Insertsort
/*See Readme
********************************/

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>

#include<string.h>
using namespace std;
  
/* Function to sort an array using insertion sort*/
void insertSort(int arr[], int n) 
{ 
   int i, j, k; 
   for (i = 1; i < n; i++) 
   { 
       k = arr[i]; 
       j = i-1; 
  
   while (j >= 0 && arr[j] > k) 
   { 
       arr[j+1] = arr[j]; 
       j = j-1; 
   } 
   arr[j+1] = k; 
   } 
} 

void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
	printf("%d ", arr[i]); 
	printf("\n"); 
}

int main() 
{
    
    clock_t start_t, end_t, total_t;
    
    //make array, enter N here
    int n;
    cout<< "PLease enter number of items to generate: ";
    cin>> n;
    int i;
    int count;
    int arr[n];
    
    
    for (int x =0; x<n; x++)
    {
        i= rand() % 1000;
       arr[x]= i;
        count++;
    }
	 start_t = clock();
    	insertSort(arr, n);
    	printArray(arr,n);

   end_t = clock();
    printf("End of the run, end_t = %ld\n", end_t);
    
    float diff ((float) end_t-(float)start_t);
    float seconds = diff/ CLOCKS_PER_SEC;
   
   printf("Total time taken by CPU: %f\n", seconds  );

    cout<<"Number of elements in Array is : ";
    cout<< n;
    printf("\n"); 
    cout<<"Confirmed of elements in Array is : ";
    cout<< count;
    printf("\n"); 
   
    return 0;
}