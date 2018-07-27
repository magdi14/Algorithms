// UVA:     924

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


template<class Value>
struct Array
{
    int n, sz;
    Value *arr;
    void Initialize()
    {
        n=0;
        sz=1;
        arr = new Value[sz];
    }
    void Destroy()
    {
        delete[] arr;
    }
    void AddLast(Value v)
    {
       if(n==sz)
       {
           sz*=2;
           Value *new_arr = new Value[sz];
           for(int i=0; i<n; i++)
           {
               new_arr[i] = arr[i];
           }
           delete[] arr;
           arr = new_arr;
       }
        arr[n++] = v;
    }
    void RemoveLast()
    {
        n--;
    }
    Value& operator[](int i)
    {
        return arr[i];
    }
};


struct Node
{
	Array<int> adj;

	void Initialize()
	{
	    adj.Initialize();
	}
	void Destroy()
	{
	    adj.Destroy();
	}
	void addNeighbour(int i)
	{
        adj.AddLast(i);
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n)
	{
	    n=_n;
	    nodes = new Node[n];
	    for(int i=0; i<n; i++)
        {
            nodes[i].Initialize();
        }
	}
	void Destroy()
	{
	    for(int i=0; i<n; i++)
            nodes[i].Destroy();
        delete[] nodes;
	}
	void addEdge(int u, int v)
	{
	    nodes[u].addNeighbour(v);
	}
};


template <class Type>
struct Queue
{
	int f, n, sz;      //f is the index of first element, n is 1+last element so to get number of element is in Q f-n;
	Type* elems;

	void Initialize(int sizee)
	{
	    sz = sizee;
	    elems = new Type[sizee];
	    f = 0;
	    n = 0;
	}
	void Destroy()
	{
	    delete [] elems;
	}
	void Add(Type t)
	{
	    elems[n] = t;
	    n++;
	}
	Type Pop()
	{
	    Type tmp = Peek();
	    f++;
	    return tmp;
	}
	Type Peek()
	{
	    return elems[f];
	}
	int Num()
	{
	    return (n-f);
	}
};
void Booming(Graph g, int start)
{
    Queue<int> q;
    bool* visited = new bool[g.n];
    int knewToday = 1, today=1, boomToday, maxBoom=0, maxDay=0;
    for(int i=0; i<g.n; i++)
        visited[i] = false;
    int cur, cursz;
    q.Initialize(g.n);
    q.Add(start);
    visited[start] = true;
    while(q.Num()>0)
    {
        boomToday = 0;
        while(knewToday--)
        {
            cur = q.Pop();
            cursz = g.nodes[cur].adj.n;
            for(int i=0; i<cursz; i++)
            {
                int x=g.nodes[cur].adj[i];
                if(!visited[i])
                {
                    q.Add(x);
                    boomToday++;
                    visited[x] = true;
                }
            }
        }
        if(boomToday > maxBoom)
        {
            maxDay = today;
            maxBoom = boomToday;
        }
        knewToday = q.Num();
        today++;

    }
    if(maxBoom == 0)
    {
        cout<<0<<endl;
    }
    else
        cout<<maxBoom<<" "<<maxDay<<endl;
    q.Destroy();
    delete[] visited;
}



int main()
{
   /*Queue<int> q;
   q.Initialize(6);
   q.Add(3);
   q.Add(5);
   q.Add(2);
   q.Add(1);
   q.Add(4);
   q.Add(7);
   cout<<q.Peek()<<endl;
   cout<<"Poped"<<endl;
   cout<<q.Num()<<endl;
   cout<<q.Pop()<<endl;
   cout<<q.Num()<<endl;
   */
   Graph g;
   int n, m, t, s;
   cin>>n;
   g.Initialize(n);
   for(int i=0; i<n; i++)
   {
       cin>>m;
       for(int q=0; q<m; q++)
       {
           cin>>s;
           g.addEdge(i,s);
       }
   }
   cin>>t;
   while(t--)
   {
       cin>>s;
       Booming(g, s);
   }
   g.Destroy();


	return 0;
}

