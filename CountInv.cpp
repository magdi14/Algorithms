// UVA:     10810

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


long long CountInvMerge(long long* a, int n)
{
    int mid = (n+1)/2;
    int i = 0, j = mid;
    int k = 0;    //index of sorted array
    long long inv_cnt = 0;
    long long* sorted = new long long[n];
    while (i<mid || j<n)
    {
        if(i>=mid && j<n)
        {
            sorted[k++] = a[j++];
        }
        else if((j >= n && i < mid)||(a[i] < a[j]))
        {
            sorted[k++]=a[i++];
        }
        else if(a[j] < a[i])
        {
            sorted[k++] = a[j++];
            inv_cnt += (mid-i);

        }

        for(int q=0; q<n; q++)
        {
            a[q] = sorted[q];
        }
        delete[] sorted;
        return inv_cnt;
    }

}
long long CountInv(long long* a, int n)
{
    if(n<=1)
    {
        return 0;
    }

    int mid = (n+1)/2;
    long long res = 0;
    res += CountInv(a, mid);
    res += CountInv(a+mid, n-mid);
    res += CountInvMerge(a, n);
    return res;
}


int main()
{
    int n ;
    long long res;
    while (cin>>n && n)
    {
        long long* arr = new long long[n];
        for(int i=0; i<n; i++)
        {
            cin>>arr[i];
        }
        res = CountInv(arr, n);
        cout<<res<<endl;
        delete[] arr;
    }
	return 0;
}

