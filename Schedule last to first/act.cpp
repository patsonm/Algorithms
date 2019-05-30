/*******
Name: Michael Patson
Homework Assignment 4

This homework corresponds part four of the homework
It is a 
last
-
to
-
start
algorithm
**********/

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

//make a structure
struct Activity {
    int numID;
    int startTime;
	int endTime;
};




void printArray(Activity arr[], int size) 
{ 
	int i; 
    cout << "The Number of Activities = " << size << endl;
	for (i=size; i >0; i--) {
	printf("%d ", arr[i-1].numID);
    }
	printf("\n"); 
}


//created a new array of activity, inserts into if end time is less than or = to the start time of the previous
//, calls print array which
//actually prints activity class id number
void lastToFirst(Activity arr[], int n)
{
    Activity actSelected[n];
    
    actSelected[0]=arr[0];
    int index=0;
    for (int x = 1; x < n; x++)
    {
        if (arr[x].endTime <= actSelected[index].startTime)
        {
             index++;
            actSelected[index]=arr[x];
           
        }
    }
    printArray(actSelected, index+1);
}

//modified from HW, did this a dumb way, kind of forgot how classes work.  look at lastTofirst function.. made a new array    
void insertSort(Activity arr[], int n) 
{ 
   int i, j, k, start, id; 
   for (i = 1; i < n; i++) 
   { 
       k = arr[i].endTime; 
       start= arr[i].startTime;
       id = arr[i].numID;
       j = i-1; 
  
   while (j >= 0 && arr[j].endTime < k) 
   { 
       arr[j+1].endTime = arr[j].endTime; 
       arr[j+1].startTime = arr[j].startTime;
       arr[j+1].numID = arr[j].numID;
       j = j-1; 
   } 
       arr[j+1].endTime = k;
       arr[j+1].startTime = start;
       arr[j+1].numID = id;   
   } 
} 
    

//inputs from file named act.txt
int main() {

    //open act.txt
    ifstream infile("act.txt");
    
    
    //not listed like tests file last week, need to manually count
    int setN = 1;
    
    while (!infile.eof()) {
        //the first number in the input file is the number activities to be input
        
        int numActivities;
        infile >> numActivities;
        
        //testing
       //cout << "num of activities " << numActivities << endl;
        
        //make an array of the activity class
        Activity a[numActivities];
        
        
        
        for (int i = 0; i < numActivities; i++) 
        {
        	infile >> a[i].numID >> a[i].startTime >> a[i].endTime;
            //cout << a[i].numID << a[i].startTime <<a[i].endTime << endl;
        }
        
        
        
        cout << "Set " << setN << endl;
        
        insertSort(a, numActivities);
        lastToFirst(a, numActivities);
        //increase test count for the next test to be read from loop
        setN++;     
    }

    
        infile.close();
        return 0;
}