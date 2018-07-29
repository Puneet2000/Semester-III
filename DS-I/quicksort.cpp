#include<iostream>
using namespace std;
void swap(int A[] ,int l,int r)
{
	int x = A[l];
	A[l]=A[r];
	A[r]=x;
}
int index(int A[],int l,int r)
{   
	int pivot=A[l];
	int i=l;
	int j=r;
	while(true)
	{
		
	while (A[i]<=pivot)
		i++;
	while (A[j]>pivot)
		j--;
	if (i<j)
	{
		swap(A,i,j);
	}
	else
	{
		swap(A,j,l);
		return j;
		
	}
}
return 0;
}

void sort(int A[],int l ,int r)
{
	if (l <r)
	{
	int q = index (A,l,r);
	sort(A,l,q-1);
	sort(A,q+1,r);
}

}
int main()
{
	int A[] = {8,7,6,5,4,3,2,1};
	sort(A,0,7);
	for(int i=0;i<8;i++)
		cout<<A[i]<<" ";
	return 0;
}