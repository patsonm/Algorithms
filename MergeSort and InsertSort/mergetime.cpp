/********************************
/* Michael Patson
/* Oregon State
/* HW Assignment 1
/* Merge time
/*See Readme
********************************/

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>

#include<string.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()



using namespace std;

//below is the function to merge arrays and input them into the new order. arr[] is being changed
void mergeArray(int arr[], int left, int middle, int right) 
{
	int size1 = middle - left + 1; 
	int size2 = right - middle; 

	//temp left and right array
	int L[size1], R[size2]; 


	//overright the previous array with the new order, checked each array, left or right

	for (int x = 0; x < size1; x++) 
	L[x] = arr[left + x]; 
	for (int y = 0; y < size2; y++) 
	R[y] = arr[middle + 1+ y]; 

	int i, j, k; 
	i = 0; // Initial index of left 
	j = 0; // Initial index of right
	k = left; // Initial index of combined 
	while (i < size1 && j < size2) 
	{ 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
			k++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
			k++; 
		} 
	} 

	//copy in left and right arrays, already Sort
	while (i < size1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	while (j < size2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

//mergeSort
void mergeSort(int arr[], int left, int right) 
{ 
	if (left < right) 
	{ 
		//calc middle 
		int middle = (left+right)/2; 

		//Sort both halves of array
		mergeSort(arr, left, middle); 
		mergeSort(arr, middle+1, right); 

		mergeArray(arr, left, middle, right); 
	} 
}

void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
	printf("%d ", arr[i]); 
	printf("\n"); 
}

/*PREVIOUS Main is left out
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

    	mergeSort(arr, 0, size-1);
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
*/


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
    mergeSort(arr, 0, n-1);
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