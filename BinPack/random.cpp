    #include <cstdlib> 
    #include <ctime> 


#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>

#include<string.h>

using namespace std;

    int main() 
    { 
        srand((unsigned)time(NULL)); 
      ofstream outfile("random.out");
        
        int numoftest=20;
        outfile<<numoftest;
        outfile<<endl;
        
        for (int i=1; i<=numoftest;i++)
        {
        
    
        
        int random_integer; 
        int numofitem;
        numofitem = (rand()%25)+1; 
        int capofbin;
        capofbin = (rand()%20)+1; 
        outfile<<capofbin;
        outfile <<endl;
        outfile<<numofitem;
        outfile <<endl;
        for(int index=0; index<numofitem; index++){ 
            random_integer = (rand()%capofbin)+1; 
            outfile << random_integer << " "; 
        } 
            outfile <<endl;
        }
    }