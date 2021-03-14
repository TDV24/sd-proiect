#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

ifstream f("numere.in");
ofstream g("timpi.out");

void bubble_sort(int v[], int n)
{
   bool ok = 1;
   int aux;
    while(ok)
    {
        ok=0;
        for(int i=0; i+1<n; ++i)
            if(v[i]>v[i+1])
            {
                aux=v[i];
                v[i+1]=v[i];
                v[i]=aux;
                ok=1;
            }
    }
}

void count_sort(int v[], int n)
{
    int v1[300001], v2[300001], maxim, i;
    maxim=v[0];
    for(i=1; i<n; i++)
        if(v[i]>maxim)
            maxim=v[i];
    for(i=0; i<=maxim; ++i)
        v1[i]=0;
    for(i=0; i<n; i++)
        v1[v[i]]+=1;
    for(i=1; i<=maxim; i++)
        v1[i]+=v1[i-1];
    for(i=n-1; i>=0; i--)
        {
            v2[v1[v[i]]-1]=v[i];
            v1[v[i]]--;
        }
    for(i=0; i<n; i++)
        v[i]=v2[i];
}

void count_sort_1(int v[], int n, int x)
{
    int v1[10], v2[300001], i;
    for(i=0; i<10; ++i)
        v1[i]=0;
    for(i=0; i<n; i++)
        v1[(v[i]/x)%10]+=1;
    for(i=1; i<10; i++)
        v1[i]+=v1[i-1];
    for(i=n-1; i>=0; i--)
        {
            v2[v1[(v[i]/x)%10]-1]=v[i];
            v1[(v[i]/x)%10]--;
        }
    for(i=0; i<n; i++)
        v[i]=v2[i];
}

void radix_sort(int v[], int n)
{
    int i;
    int maximum=v[0];
    for(i=1; i<n; i++)
        if(v[i]>maximum)
            maximum=v[i];
    for(int i=1; maximum/i>0; i*=10)
        count_sort_1(v,n,i);
}

void prog1(int v[], int a, int b, int c)
{
    int x1, x2, i, j, k;
    x1=b-a+1;
    x2=c-b;
    int v1[300001], v2[300001];
    for(i=0; i<x1; i++)
        v1[i]=v[a+i];
    for(j=0; j<x2; j++)
        v2[j]=v[b+1+j];
    i=j=0;
    k=a;
    while(i<x1 && j<x2)
    {
        if(v1[i]<v2[j])
        {
            v[k]=v1[i];
            i++;
        }
        else
        {
            v[k]=v2[j];
            j++;
        }
        k++;
    }
    while(i<x1)
    {
        v[k]=v1[i];
        i++;
        k++;
    }
    while(j<x2)
    {
        v[k]=v2[j];
        j++;
        k++;
    }

}

void merge_sort(int v[], int d, int n)
{
    if(d>=n)
        return;
    else
    {
        int u=d+(n-d)/2;
        merge_sort(v, d, u);
        merge_sort(v, u+1, n);
        prog1(v, d, u, n);
    }
}

int prog2(int v[], int x, int y)
{
    int p, s, i, aux;
    p=v[y];
    s=x-1;
    for(i=x; i<=y-1; i++)
        if(v[i]<p)
            {
                s++;
                aux=v[s];
                v[s]=v[i];
                v[i]=aux;
            }
    aux=v[s+1];
    v[s+1]=v[y];
    v[y]=aux;
    return(s+1);

}

void quick_sort(int v[], int a, int b)
{
    if(a<b)
    {
        int x=prog2(v, a, b);
        quick_sort(v, a, x-1);
        quick_sort(v, x+1, b);
    }
}

int main()
{
    int n, v[300001], v2[300001], i, j;
    f>>n;
    for(i=0; i<n; i++)
        {
            f>>v[i];
            v2[i]=v[i];
        }
    for(i=1; i<=6; i++)
    {
        for(j=0; j<n; j++)
            v[j]=v2[j];
        if(i==1)
        {
            auto start = high_resolution_clock::now();
            sort(v, v+n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            g<<"c++ sort: "<<duration.count()<<'\n';
        }

        if(i==2)
        {
            auto start = high_resolution_clock::now();
            bubble_sort(v, n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            g<<"Bubble sort: "<<duration.count()<<'\n';
        }
        if(i==3)
        {
            auto start = high_resolution_clock::now();
            count_sort(v, n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            g<<"Count sort: "<<duration.count()<<'\n';
        }
        if(i==4)
        {
            auto start = high_resolution_clock::now();
            radix_sort(v, n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            g<<"Radix sort: "<<duration.count()<<'\n';
        }
        if(i==5)
        {
            auto start = high_resolution_clock::now();
            merge_sort(v, 0, n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            g<<"merge sort: "<<duration.count()<<'\n';
        }
        if(i==6)
        {
            auto start = high_resolution_clock::now();
            quick_sort(v, 0, n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            g<<"quick sort: "<<duration.count()<<'\n';
        }
    }
    return 0;
}
