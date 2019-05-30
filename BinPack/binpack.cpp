
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<string.h>
#include <algorithm> 
using namespace std;



/*********
int firstFit(int weight[], int n, int c) 
{ 
  
   int result = 1, bin_rem = c; 
  

   for (int i=0; i<n; i++) 
   { 
       //create new bin
       if (weight[i] > bin_rem) 
       { 
          result++;
          bin_rem = c - weight[i]; 
       } 
       else
         bin_rem -= weight[i]; 
   } 
   return result; 
} 
***********/


//modified from https://www.geeksforgeeks.org/bin-packing-problem-minimize-number-of-used-bins/

int firstFit(int weight[], int n, int c) 
{ 
    //set first bin count to0
    int result = 0; 
  
    //set limit on bins
    int bin_rem[n]; 
  
  //find ites to put in bins
    for (int i=0; i<n; i++) 
    { 
        //can this bind fit it?
        int j; 
        for (j=0; j<result; j++) 
        { 
            if (bin_rem[j] >= weight[i]) 
            { 
                bin_rem[j] = bin_rem[j] - weight[i]; 
                break; 
            } 
        } 
  
        // this is outside scope of project, but more robust if we need future dsize
        if (j==result) 
        { 
            bin_rem[result] = c - weight[i]; 
            result++; 
        } 
    } 
    return result; 
} 


//modified from https://www.geeksforgeeks.org/bin-packing-problem-minimize-number-of-used-bins/

int bestFit(int weight[], int n, int c) 
{  
    int result = 0; 
  
   //need to create an array which will store bin space left
    int bin_rem[n]; 
  
    // Place items one by one 
    for (int i=0; i<n; i++) 
    { 
        //which bin has the closes space left
        int j; 
  
       //space left and new bin?
        int min = c+1, bi = 0; 
  
        for (j=0; j<result; j++) 
        { 
            if (bin_rem[j] >= weight[i] && 
                    bin_rem[j] - weight[i] < min) 
            { 
                bi = j; 
                min = bin_rem[j] - weight[i]; 
            } 
        } 
  
        
        // create a new bin 
        if (min==c+1) 
        { 
            bin_rem[result] = c - weight[i]; 
            result++; 
        } 
        else 
            //put items in bing
            bin_rem[bi] -= weight[i]; 
    } 
    return result; 
} 


//modified from https://www.geeksforgeeks.org/bin-packing-problem-minimize-number-of-used-bins/
int firstFitDec(int weight[], int n, int c) 
{ 
    //need to sort 
    sort(weight, weight+n, std::greater<int>()); 
  //now call first fit
    return firstFit(weight, n, c); 
} 

int main(){

// Input and output file open

	ifstream infile("bin.txt");
   
    int testCase;
    infile >> testCase; 
    
    //remove
    //cout << testCase;
    //cout << endl;
    int totalFF=0, totalRF =0, totalBF=0;
    for (int i = 0; i < testCase; i++) // for each test case
    {
        int binCap; // num of items
        infile >> binCap;
        
        //remove
        //cout << binCap;
        //cout << endl;
        
        int items;
        
        //remove 
        
        
        infile >> items;
        int weight[items];
        //cout << items;
        //cout << endl;
  
        for (int j = 0; j < items; j++)
        {
            infile >> weight[j];
        }
       int nFit=0, bFit=0, rFit=0;
    nFit=firstFit(weight, items,binCap);
    bFit=bestFit(weight, items,binCap);
    rFit=firstFitDec(weight, items,binCap);
    
    totalFF=totalFF+ nFit;
    totalRF=totalRF+rFit;
    totalBF=totalBF+bFit;
    cout <<"Test Case ";
    cout <<i+1 << " First Fit: " << nFit<<" First Fit Decreasing: "<<rFit <<" Best Fit: "<<bFit;
        
        
        cout <<endl;
    }

    

    

    // Closing input and output files

    infile.close();
    //below is used for part c
   // cout<<"First fit: "<<totalFF<<" Best Fit: "<< totalBF << " First Fit Reversed: "<<totalRF<< endl;
    return 0;
}