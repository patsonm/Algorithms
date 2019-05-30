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
	// Input and output file open

	ifstream infile("data.txt");
	ofstream outfile("stooge.out");

	// Every line read stored in "line" string

	string line;
	int i;

	// reading line by line

	while (getline(infile, line))
	{
		// Tokenizing each line into array size and array elements

    	istringstream iss(line);

    	int size;

    	infile>>size;

    	int arr[size];

    	for(i=0;i<size;i++)
    		infile>>arr[i];

    	// Calling merge sort and print array

    	STOOGESORT(arr,0,(size-1));
    	printArray(arr,size);

    	// Printing sorted array to output file
    	for(i=0;i<size;i++)
    		outfile<<arr[i]<<" ";
    	outfile<<endl;
    }

    // Closing input and output files

    infile.close();
    outfile.close();

    return 0;
}