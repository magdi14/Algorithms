// UVA:     10954

#include <bits/stdc++.h>
using namespace std;
template <class value>
struct Array
{
    int n, sz;
    value *arr;
    void Initialize()
    {
        n=0;
        sz=1;
        arr = new value[sz];
    }
    void Destroy()
    {
        delete[] arr;
    }
    void AddLast(value v)
    {
       if(n==sz)
       {
           sz*=2;
           value *new_arr = new value[sz];
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
    value& operator[](int i)
    {
        return arr[i];
    }
    void print()
    {
        for(int i=0; i<n; i++)
        {
            cout<<arr[i]<<" ";
        }
    }

};

template <class elem>
struct Heap
{
    Array <elem> h;
    bool (*IsBefore)(elem& a, elem& b);
    void Initialize(bool (*_IsBefore)(elem&, elem&))
    {   IsBefore  = _IsBefore;
        h.Initialize();
    }
    void Destroy()
    {
        h.Destroy();
    }
    int Child(int i)
    {
        return (2*i)+1;
    }
    int Parent(int i)
    {
        return floor((i-1)/2);
    }
    void MoveUp(int ind)
    {
        int cur = ind;
        int parent;
        bool swapped = false;
        do
        {
            parent = Parent(cur);
            swapped = IsBefore(h[cur], h[parent]);
            if(swapped)
            {
                swap(h[cur], h[parent]);
            }
            cur = parent;
        }while (swapped);
    }
    void MoveDown(int ind)
    {
        int cur = ind;
        int child1, child2;
        int swapping;
        bool swapped;
        do
        {
            swapping = cur;
            child1 = Child(cur);
            child2 = child1+1;
            swapped = false;
            if(IsBefore(h[child1], h[cur]) && child1 < h.n)
            {
                swap(h[child1], h[cur]);
                swapping = child1;
                swapped = true;
            }
            if(IsBefore(h[child2], h[cur]) && child2 < h.n)
            {
                swap(h[child2], h[cur]);
                swapping = child2;
                swapped = true;
            }
            cur = swapping;
        }while (swapped);


    }
    void Add(elem e)
    {
        h.AddLast(e);
        MoveUp(h.n-1);
    }
    elem GetFirst()
    {
        return h[0];
    }
    elem RetrieveFirst()
    {
        elem el = h[0];
        swap(h[0], h[h.n-1]);
        h.RemoveLast();
        MoveDown(0);
        return el;
    }
    void print()
    {
        h.print();
    }
    int HeapSize()
    {
        return h.n;
    }
};

template <class elem>
bool IsBeforee(elem& a, elem& b)
{
    return a<b;
}



int main() {
    Heap<int> myheap;
    int n, value, cost, sumCost, num1, num2;
    while (true)
    {
        cin>>n;
        if(n<=0)
            break;
        myheap.Initialize(IsBeforee<int>);
        sumCost = 0;
        //cout<<"ana hena"<<endl;
        for(int i=n; i>0; i--)
        {
            cin>>value;
            myheap.Add(value);
        }
        while(myheap.HeapSize() > 1)
        {
            num1 = myheap.RetrieveFirst();
            num2 = myheap.RetrieveFirst();
            cost = num1+num2;
            sumCost+=cost;
            myheap.Add(cost);
        }
        cout<<sumCost<<endl;
        myheap.Destroy();

    }




    return 0;
}
