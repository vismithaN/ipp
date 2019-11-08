#include<iostream>
#include "omp.h"
#include<cstdlib>
using namespace std;
void print(int a[], int l,int r)
{
	for(int i=l; i<=r; i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

void merge(int a[], int l, int m, int r)
{
	
	int L[m-l+1],R[r-m];
	
	#pragma omp parallel for schedule(dynamic)
	for(int i=0; i<(m-l+1); i++)
		L[i]=a[l+i];
	#pragma omp parallel for schedule(dynamic)
	for(int i=0; i<(r-m); i++)
		R[i]=a[m+1+i];
	int i=0, j=0, k=l;
	
	while(i<(m-l+1) && j<(r-m))
	{
		if(L[i]<R[j])
			a[k]=L[i++];
		else
			a[k]=R[j++];
		k++;
	}
	
	while(i<(m-l+1))
		a[k++]=L[i++];
	while(j<(r-m))
		a[k++]=R[j++];
	//print(a,l,r);

}
/* 
This function is the main hotspot of the algorithm which I have chosen to parallelise
The calls labelled call 1 and call 2 are essentially independent since they are operating on distinct
parts of the array and hence can be called in parallel.
*/

void mergeSort(int a[], int l, int r)
{
	if(l<r)
	{
		int m=(l+r)/2;
		omp_set_nested(7);
		
		#pragma omp parallel sections num_threads(4)
		{
		cout<<omp_get_num_threads()<<endl;
		
			#pragma omp section
			{
			//cout<<"wqheqwe "<<omp_get_nested()<<"nested\n";
				//cout<<"executed by thread= "<<omp_get_thread_num()<<endl;
				mergeSort(a,l,m);
			}
			#pragma omp section
			{
	
				//cout<<"executed by thread= "<<omp_get_thread_num()<<endl;
				mergeSort(a,m+1,r);
			}
		
		}
		merge(a,l,m,r); 
	}
}

int main()
{
	int n;
	cout<<"enter the number of elements\n";
	cin>>n;
	int a[n];
	cout<<"enter the array elements\n";
	for(int i=0; i<n; i++)
		a[i]=(int)random()%1000;
	cout<<"\nUnsorted array; ";
	print(a,0,n-1);

	double t1=omp_get_wtime();
	mergeSort(a,0,n-1);
	double t2=(omp_get_wtime()-t1);

	cout<<"\nSorted array: ";
	print(a,0,n-1);
	cout<<"time: "<<t2;
	return 0;
	}

