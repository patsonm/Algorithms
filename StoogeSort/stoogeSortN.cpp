/*******
Name: Michael Patson
Homework Assignment 2

Stoogesort pseudocode
StoogeSort(A[0 ... n - 1])
if n = 2 and A[0] > A[1]
swap A[0] and A[1] else if n > 2
m = ceiling(2n/3) StoogeSort(A[0 ... m - 1]) 
StoogeSort(A[n - m ... n - 1]) 
Stoogesort(A[0 ... m - 1])
**********/


#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<math.h>
#include<string.h>
using namespace std;
  

void STOOGESORT(int arr[], int left, int h)
{
    int n = h-left+1;
    
    if ((n==2) &&(arr[left]>arr[h]) )
        swap(arr[left],arr[h]);
    else if (n > 2)
    {
        //split into thirds(calcs third way)
        int third= floor(n/3);
        
        //recurive yosrt first 2/3
        STOOGESORT(arr, left, (h - third));
        //recurive yosrt last 2/3
        STOOGESORT(arr, (left+third), h);
            //sort first 2/3 again
         STOOGESORT(arr, left, (h - third));
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
    	STOOGESORT(arr,0,(n-1));
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