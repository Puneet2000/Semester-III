#include<iostream>
using namespace std;
void Heapify (int A[] ,int n ,int pos)
{
	int smallest = pos;
	int right = 2*pos +2;
	int left = 2*pos +1;
	if (left<n && A[left] < A[smallest])
	{
       smallest = left;
	}
   
    if(right<n && A[right]<A[smallest])
    	smallest = right;

    if (smallest != pos)
       {
       	int y = A[pos];
       	A[pos]=A[smallest];
       	A[smallest]= y;
       	Heapify (A,n,smallest);
       }
}

void Build(int A[],int n)
{
	for (int i=(n-1)/2;i>=0;i--)
		Heapify(A,n,i);
}
void Heapsort(int A[] , int n)
{
	Build(A,n);
	int size= n;
	for (int i=n-1;i>=0;i--)
	{
		cout<<A[0]<<" ";
		int x =  A[0];
		A[0] = A[i];
		A[i]= x;

        size= size-1;
		Heapify(A,size,0);
	}
}

void DecreaseKey (int A[] ,int x,int pos)
{
	A[pos]=x;
	int position = pos;
	int parent = (pos-1)/2;
	for(int i= (parent);i>=0;i--)
	{
		if(A[parent]>A[position])
		{
			int  y = A[parent];
			A[parent]=A[position];
			A[position]=y;
			position=parent;
			parent = (parent-1)/2;
		}
		else
			break;
	}
}
int main()
{
	int n;
	cin>>n;
	int a[n];
	for (int i=0;i<n;i++)
		cin>>a[i];

	Build(a,n);
     DecreaseKey(a,0,5);
	for (int i=0;i<n;i++)
		cout<<a[i]<<" ";

	

	return 0;
}