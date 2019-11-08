#include<omp.h>
#include<iostream>
#include<iomanip>
#include<cstdio>
using namespace std;

int main()
{
int nthread,tid;
int m,n,p,q;
cout<<"enter the matrix size of matrix A\n";
cin>>m>>n;
cout<<"enter the matrix size of matrix B\n";
cin>>p>>q;
if(n!=p)
{
	cout<<"wrong size\n";
	return 0;
}

int a[m][n],b[p][q],c[m][q];
double t1=omp_get_wtime();
#pragma omp parallel for schedule(dynamic,4)//matrix A
for(int i=0;i<m;i++)
{
	//printf("Row %d by %d\n",i,omp_get_thread_num());
	for(int j=0;j<n;j++)
	{
		a[i][j]=i+j;
	}
}



#pragma omp parallel for schedule(dynamic,4)//matrix B


for(int i=0;i<p;i++)
{
	//printf("Row %d by %d\n",i,omp_get_thread_num());
	for(int j=0;j<q;j++)
	{
		b[i][j]=i+j;
	}
}
#pragma omp parallel for schedule(dynamic,4)
for(int i=0;i<m;i++)
	for(int j=0;j<q;j++)
		c[i][j]=0;



#pragma omp parallel for schedule(dynamic,4)//computing C
for(int i=0;i<m;i++)
{
	//printf("%d executes row %d\n",i,omp_get_thread_num());
	for(int j=0;j<q;j++)
	{
		for(int k=0;k<n;k++)
		{
			c[i][j]+=(a[i][k]*b[k][j]);
		}
	}
}

double t2=omp_get_wtime();
cout<<"matrix reults\n";
for(int i=0;i<m;i++)
{

	for(int j=0;j<q;j++)
	{
		cout<<c[i][j]<<" ";
	}
	cout<<"\n";
}
cout<<"clock time "<<t2-t1;
return 0;
}


	






