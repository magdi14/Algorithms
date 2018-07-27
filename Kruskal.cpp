// UVA:     11631

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;
	int MaxN;

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
                MaxN = max(MaxN, num_nodes[nod1]);
                return true;
            }
            else
            {
                parent[nod1] = nod2;
                num_nodes[nod2] += num_nodes[nod1];
                MaxN = max(MaxN, num_nodes[nod2]);
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
	   return MaxN;

	}
};


template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = (n+1)/2;
    int i=0, j=mid;
    int k=0; //index of temp array
    Type* sorted = new Type[n];
    while(i<mid&&j<n)
    {
        if(i>=mid&&j<n)
        {
            sorted[k++] = a[j++];
        }
        else if((j>=n&&i<mid)||(IsBefore(a[i], a[j])))
        {
            sorted[k++] = a[i++];
        }
        else
        {
            sorted[k++] = a[j++];
        }
    }
    for(int q=0; q<n; q++)
    {
        a[q] = sorted[q];
    }
    delete[] sorted;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{  if(n<=1)
     return;
  int mid = (n+1)/2;
  MergeSort(a, mid, IsBefore);
  MergeSort(a+mid, n-mid, IsBefore);
  Merge(a, n, IsBefore);
}


struct Edge
{
	int u, v;
	int w;
	void printt()
	{
	    cout<<u<<" "<<v<<" "<<w<<endl;
	}
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}


int main()
{
    DisjointSets dis;
    Edge* edges;
    int n,m, totalcost, j;
    while(cin>>m>>n && m && n)
    {
        dis.Initialize(m);
        edges = new Edge[n];
        totalcost = 0;
        for(int i = 0; i<n; i++)
        {
            cin>>edges[i].u>>edges[i].v>>edges[i].w;
            totalcost+=edges[i].w;
        }
        MergeSort<Edge>(edges, n, IsBeforeEdge);
        //for(int i=0; i<n; i++)
         //   edges[i].printt();
        j = 0;
        while(dis.getMax() < m)
        {
            if(dis.Union(edges[j].u, edges[j].v))
                totalcost-=edges[j].w;
            j++;
        }
        cout<<totalcost<<endl;
        delete[] edges;
        dis.Destroy();

    }

	return 0;
}

