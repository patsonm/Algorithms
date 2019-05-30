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
	// Input and output file open

	ifstream infile("data.txt");
	ofstream outfile("merge.out");

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

    	insertSort(arr, size);
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