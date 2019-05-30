/*******
Name: Michael Patson
Homework Assignment 3

This homework corresponds to the Acme Super Store question
**********/


#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<string.h>
using namespace std;

int knapsack(int price[], int weight[], int famMember, int items)
{
    int K[items + 1][famMember + 1];
        for (int i = 0; i <= items; i++) //go thru all the items
        {
            for (int x = 0; x <= famMember; x++) //go thru all the weights()
                {
                    if(i==0||x==0) //to carry 0 itmes
                        K[i][x] = 0; 
                    else if(weight[i-1]<= x)
                    {
                        K[i][x] = max(price[i - 1] + K[i - 1][x - weight[i - 1]], K[i - 1][x]); //choose the ma value
                    }
                    else
                        K[i][x] = K[i - 1][x]; //no room in the knapsack
                }
        }
    return K[items][famMember]; 
}

void printKnapsack(int price[], int weight[], int famMember, int items, ofstream &outfile) // solves an 0-1 knapsack problem
{
       int K[items + 1][famMember + 1];
        for (int i = 0; i <= items; i++) //go thru all the items
        {
            for (int x = 0; x <= famMember; x++) //go thru all the weights()
                {
                    if(i==0||x==0) //to carry 0 itmes
                        K[i][x] = 0; 
                    else if(weight[i-1]<= x)
                    {
                        K[i][x] = max(price[i - 1] + K[i - 1][x - weight[i - 1]], K[i - 1][x]); //choose the ma value
                    }
                    else
                        K[i][x] = K[i - 1][x]; //no room in the knapsack
                }
        }

    int knapsackSum= K[items][famMember]; 
    
    int weightCap = famMember; 
    int order = 0;
    int print[items];
    
    //looking at the table, need to eigher include the result or move over inteh table
    
    for (int i = items; i > 0 && knapsackSum > 0; i--) { 
          
        if (knapsackSum == K[i - 1][weightCap])
            continue;         
        else { 
  
            // This item is included. 
            order++;
            print[order]=i;
            
            //outfile << i << " "; 
            
            //need to reverse this
              
            
            knapsackSum = knapsackSum - price[i - 1]; 
            weightCap = weightCap - weight[i - 1]; //weight avaiable in backback
        } 
    }
    //loop to write output of each fam member
    for (int i = order; i>0; i--)
    {
        outfile << print[i] << " "; 
    }
    
}


int totalVal(int price[],int weight[],int famMember[],int items,int numfam)
{
    //use this to store total 
    
    int totalValue = 0;
    //this loops thru each user in the fam using the famMember array
    for (int i = 0; i < numfam; i++)
    {
        totalValue = totalValue + knapsack(price, weight, famMember[i], items); //remember to pass in fam member here 
    }
    return totalValue;
}


//copied from mpatson 165 project
int max(int a, int b) 
{ 
    return (a > b)? a : b; 

}


/*did not use this for this project, copied from hw2
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
	printf("%d ", arr[i]); 
	printf("\n"); 
}
*/


int main() 
{
	// Input and output file open

	ifstream infile("shopping.txt");
	ofstream outfile("shopping.out");
   
    
    //first get input cases
    int testCase;
    infile >> testCase; 
    
    
    for (int i = 0; i < testCase; i++) // for each test case
    {
        int items; // num of items
        infile >> items;
    
        
        //make two arrays to store the items and loop thru price weight
        int price[items], weight[items]; //makes an array for each test case
  
        for (int j = 0; j < items; j++)
        {
            infile >> price[j]; infile >> weight[j];
        }
    
        //next line is fam number, repeat this like with test case
        int numFam; 
        infile >> numFam;
        int famMember[numFam];
        
        //loop thru fam member weight
        for (int j = 0; j < numFam; j++)
        {
            infile >> famMember[j]; 
        }
        //rest is for output file
        outfile << "Test case " << i+1 << endl;

        outfile << "Total Price " << totalVal(price, weight, famMember, items, numFam) << endl; // add solution to outputfile
        outfile << "Member Items" << endl;
       
        //loops thru each for output of fam member, what each fam member carries
        for (int z = 0; z < numFam; z++)
        {
            outfile << z + 1 << ": ";  
            printKnapsack(price, weight, famMember[z], items, outfile);
            outfile << endl;
        }
            //make a space for outfile 
        outfile << endl;
    }



    // Closing input and output files

    infile.close();
    outfile.close();

    return 0;
}