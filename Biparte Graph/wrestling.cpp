/*******************************************
Michael Patson
Oregon State CS325
Homework Assignment 5 Wrestler Matchups
*******************************************/


#include <bits/stdc++.h>
#define MAX 100

using namespace std;

vector<int> adj[MAX];//adjancy matrix
bool visited[MAX];//for dfs only


//the general stragedy for depth first seach was evaluated and modified from https:
//www.geeksforgeeks.org/check-if-a-given-graph-is-bipartite-using-dfs/

int dfs(int e, int start, int *babyface)
{
   visited[e] = 1;//marks the edge as visited
   int v;
   babyface[e] = 1-babyface[start];

   for(int i=0; i<adj[e].size(); i++)
   {
       v = adj[e][i];
       if(!visited[v])//only checks if not visited
       {
           dfs(v,e, babyface);
       }
       else
       {
           //else if the nodes have the same value, cannot be bipartite
           if(babyface[v] == babyface[e])
               //fail
               return 0;
       }
   }
    //yes based
   return 1;
}

int main(int argc, char * args[]) 
{

    int u, v;///standard vertix naming convention
    string name1,name2;
    
    int bipartite=1;
    

    map<string, int> map;
    
    ifstream fin(args[1]);
    //if cannot find file return error and display text to terminal
    if (!fin) 
    {
        cout << "Could not find file\n";
        
        return 0;
    }

   
    //gets the numer of names and indexs them so we can use dfs
    int n;
    
    fin>>n;
    int babyface[n];//to check which values belong in babyface
    babyface[0] = 0;
    //create an array string to hild anme
    string names[n+1];

    
    
   for(int i=1;i<=n;i++)
   {
       fin>>name1;
       map[name1] = i;
       names[i] = name1;
   }
    
    int rivals;
   fin>>rivals;

    //the rivals are the edges, the map indexs them for graphiing
   for(int i=1; i<=rivals; i++)
   {
       fin>>name1>>name2;
       u = map[name1]; v = map[name2];//getting indeices of the names
       adj[u].push_back(v); adj[v].push_back(u);//adding edges to the graph
   }



   //perform dfs for all the connected components and get a possible answer
   for(int i=1;i<=n;i++)
   {
       if(visited[i])
           continue;
       bipartite = dfs(i, 0, babyface);
       if(bipartite==0)
           break;
   }

   if(bipartite==0)
   {
       cout<<"No";
       cout<< endl;
       return 0;
   }

   //vector to hodl the difference names 
    vector<string> babyfaces;
    vector<string> heels;
    
    for(int i=1; i<= n; i++)
    {
    
    if(babyface[i])
        babyfaces.push_back(names[i]);
    else
        heels.push_back(names[i]);
    }

    
    //if bipart
    cout << "Yes";
    cout << endl;

    
    //output for bby faces
    cout<<"Babyfaces:";
    for(int i=0;i<babyfaces.size();i++)
    {
    cout<<" "<<babyfaces[i];
    }
    cout<<endl;
    
    //output for heels
    cout<<"Heels:";
    for(int i=0;i<heels.size();i++)
    {
    cout<<" "<<heels[i];
    }
    cout<<endl;

    return 0;
}