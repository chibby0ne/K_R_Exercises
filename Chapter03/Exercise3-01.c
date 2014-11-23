#include <stdio.h>
#define NUM 8
#define X 4
int binsearch(int x, int v[], int n);

int main()
{
    int v[NUM];
    int i,x;
    for (i=0; i<NUM; i++)
        v[i]=i;
    x=binsearch(X,v,NUM);
    printf("The index that holds number: %d is: %d",X,x);
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low,mid,high;
    low=0;
    high=n-1;
    mid=(low+high)/2;
    while ((low<=high) && (x!=v[mid]))
    {

        if (x < v[mid])
            high=mid-1;
        else
            low=mid+1;
        mid=(low+high)/2;
    }
    if(x==v[mid])
        return mid;
    else
        return -1;
}

//int binsearch(int x, int v[], int n)
//{
//    int low,mid,high;
//    low=0;
//    high=n-1;
//    while ((low<=high))
//    {
//        mid=(low+high)/2;
//        if (x < v[mid])
//            high=mid-1;
//        else if (x > v[mid])
//            low=mid+1;
//        else
//            return mid;
//    }
//    return -1;
//}
