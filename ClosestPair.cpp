#include <bits/stdc++.h>
using namespace std;

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    int right = mid;
    int left = 0;
    Type* sorted = new Type[n];
    int k = 0;    // index of start of sorted array
    while(left < mid || right < n)
    {
        if(left >= mid && right < n )
        {
            sorted[k++] = a[right++];
        }

        else if (left<mid&&right>=n)
            sorted[k++] = a[left++];

        else
        {
            if(IsBefore(a[left], a[right]))
                sorted[k++] = a[left++];
            else
                sorted[k++] = a[right++];

        }
    }
    for(int i = 0; i<n; i++)
    {
        a[i] = sorted[i];
    }
    delete[] sorted;

}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n<=1)
        return;

    int mid = n/2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a+mid, n-mid, IsBefore);
    Merge(a, n, IsBefore);
}

struct Point
{
	double x, y;
};

bool IsBeforeX(Point& a, Point& b)
{
    return a.x < b.x;
}
bool IsBeforeY(Point& a, Point& b)
{
    return a.y < b.y;
}

double dist(Point& a, Point& b)
{
    double dist = sqrt(((a.x-b.x)*(a.x-b.x)) + ((a.y-b.y)*(a.y-b.y)));
    return dist;
}

double getMinDistance(Point* p, int n)
{
    double mind = 99999999999;
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {    double tmp = dist(p[i], p[j]);
            if(tmp < mind)
                mind = tmp;
        }
    }
    return mind;

}

double closestStrip(Point* strip, int siz, double dis)
{
    double mindStrip = dis;
    MergeSort(strip, siz, IsBeforeY);

    for(int i=0; i<siz; i++)
    {
        for(int j= i+1; j<siz; j++)
        {
            if(strip[j].y - strip[i].y < mindStrip)
                break;

            double tmp = dist(strip[i], strip[j]);
            if( tmp < mindStrip)
                mindStrip = tmp;
        }
    }
    return mindStrip;

}


double ClosestPair(Point* p, int n)
{   if(n<=3)
     {
         return getMinDistance(p, n);
     }
    int midPoint = n/2;
    double distl = ClosestPair(p, midPoint);
    double distr = ClosestPair(p+midPoint, n-midPoint);
    double d = min(distl, distr);
    Point* strip = new Point[n];
    int contStrip = 0;
    Point mid = p[midPoint];
    for(int  i = 0; i<n; i++)
    {
        if(abs(p[i].x - mid.x) < d)
        {
             strip[contStrip] = p[i];
             contStrip++;
        }
    }
    return min(d, closestStrip(strip, contStrip, d));
}

int main()
{
    /*
    Point* arr = new Point[3];
    for(int i=0; i<3; i++)
    {
        cin>>arr[i].x;
        cin>>arr[i].y;
    }
    double d=dist(arr[0], arr[1]);
    MergeSort(arr, 3, IsBeforeX);
    for(int i=0; i<3; i++)cout<<arr[i].x<<" "<<arr[i].y<<endl;
    cout<<"Smallest distance: "<<ClosestPair(arr, 3)<<endl;
    */
    int n;
    double res = 0;
    while(cin>>n && n)
    {
        Point* p = new Point[n];
        for(int i=0; i<n; i++)
            cin>>p[i].x>>p[i].y;
        MergeSort(p, n, IsBeforeX);
        res = ClosestPair(p, n);
        if(res<10000)
            cout<<fixed<<setprecision(4)<<res<<endl;
        else
            cout<<"INFINITY"<<endl;

    }

	return 0;
}
