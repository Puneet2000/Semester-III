#include<iostream>
using namespace std;
unsigned int factorial(unsigned int n) 
{ 
    if (n == 0) 
      return 1; 
    return n*factorial(n-1); 
} 
int main(){
	for(int i=1;i<=59999;i++){
		unsigned long long int sum =0,dsum=0;

		int j =i;
		while(j!=0){
			int d = j%10;
			dsum+=d;
			sum += factorial(d);
			j=j/10;
		}
		if(i==sum){
			cout<<"r1 : 1";
		}
		else
			cout<<"r1 : 0";
		cout<<endl;

		if(i==dsum*dsum*dsum)
			cout<<"r2 : 1";
		else
			cout<<"r2 : 0";
		cout<<endl;
	}
	return 0;
}
