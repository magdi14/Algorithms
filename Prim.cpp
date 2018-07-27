// UVA:     534

#include <bits/stdc++.h>
#include <iostream>
using namespace std;


template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

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
            Value *tmp = new Value[sz];
            for(int i=0; i<n; i++)
            {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;
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


struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	int x, y; // x and y coordinates of the node
	Array<Edge> adj;

	void Initialize()
	{
	    adj.Initialize();
	}
	void Destroy()
	{
	    adj.Destroy();
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
        {
            nodes[i].Destroy();
        }
	}

};


// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    double left = 0, right = v,mid;

    while(left<right && n--)
    {
        mid = (left+right)/2;
        //cout<<fixed<<setprecision(20)<<mid<<endl;
       // cout<<"Left:"<<fixed<<setprecision(20)<<left;
        //cout<<"    Right:"<<fixed<<setprecision(20)<<right<<endl;

        if(mid*mid==v)
            return mid;
        else if (mid*mid>v)
            right = mid;

        else
            left = mid;
   }
   return mid;
}
double calcDistance(Node nod1, Node nod2)
	{
	    double dis1 = (nod1.x - nod2.x) * (nod1.x - nod2.x);
	    double dis2 = (nod1.y - nod2.y) * (nod1.y - nod2.y);

	    return Sqrt(dis1+dis2);
	}
	Edge getMin(Array<Edge> eg)
	{   Edge tm = eg[0];
	    for(int i=1; i<eg.n; i++)
	    {
	        if(eg[i].w<tm.w)
                tm = eg[i];
	    }
	    return tm;
    }


int main()
{
    //freopen("input.in", "r", stdin);
   Graph g;
   int t;
   int x,y;
   int cnt=0;
   while(cin >> t && t)
   {
       g.Initialize(t);
       for(int i=0; i<t; i++)
       {
           cin>>g.nodes[i].x>>g.nodes[i].y;
       }
       for(int i=0; i<t; i++)
       {
           Node nd1 = g.nodes[i];
           for(int j=0; j<t; j++)
           {
                if(i==j)
                 break;
              Node nd2 = g.nodes[j];
              Edge eg;
              eg.v = j;
              eg.w = calcDistance(nd1, nd2);
              g.nodes[i].adj.AddLast(eg);

              eg.v = i;
              g.nodes[j].adj.AddLast(eg);
           }
       }
         double cost = 0;
         Array<Edge> cure;
         cure.Initialize();
         Edge cur;
        for(int i=0; i<t; i++)
        {
           for(int j=0; j<g.nodes[i].adj.n; j++)
           {
                cur = g.nodes[i].adj[j];
                cure.AddLast(cur);
                Edge minn = getMin(cure);
                if(minn.v == 1)
                {
                    cout<<cnt<<" "<<cost+minn.w;
                }
                else
                {
                    cur = minn;
                }
          }

        }
       for(int i=0; i<t; i++){
            cout <<"Node: " << i <<endl;
            for(int j=0; j<g.nodes[i].adj.n; j++){
                cout << g.nodes[i].adj[j].v<<" "<<g.nodes[i].adj[j].w<<endl;
            }
            cout <<endl;
       }



   }
	return 0;
}

