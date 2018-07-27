// UVA:     10608

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;


	void Initialize(int _n)
	{
	    n = _n;
	    parent = new int[n+1];
        num_nodes = new int[n+1];
	    for(int i=1; i<=n; i++)
        {
            parent[i] = i;
            num_nodes[i] = 1;
        }
	}

	int Find(int i)
	{
	    int tm = i;
	   // int p = i;
	    do
        {
            tm = parent[tm];

        }while(parent[tm]!= tm);

        //parent[p] = tm;

        return tm;
	}
	bool Union(int i, int j)
	{
	    int nod1 = Find(i);
	    int nod2 = Find(j);
	    if(nod1!=nod2)
        {
            if(num_nodes[nod1]>=num_nodes[nod2])
            {
                parent[nod2] = nod1;
                num_nodes[nod1] += num_nodes[nod2];

                return true;
            }
            else
            {
                parent[nod1] = nod2;
                num_nodes[nod2] += num_nodes[nod1];
                return true;
            }
        }
        else
            return false;

	}
	void Destroy()
	{
	    delete[] parent;
	    delete[] num_nodes;
	}
	int getMax()
	{
	   int tmp=0;
	   for(int i=1; i<=n; i++)
       {
           if(num_nodes[i]>tmp)
            tmp = num_nodes[i];
       }
       return tmp;
	}
};


int main()
{
    int t, n, m, a, b;
    DisjointSets people;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        people.Initialize(n);
        for(int i=0; i<m; i++)
        {
            cin>>a>>b;
            people.Union(a, b);
        }
       cout<<people.getMax()<<endl;
        people.Destroy();
    }

	return 0;
}

