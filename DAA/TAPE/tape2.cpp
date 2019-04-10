//Round robin multiple tapes of variable size
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

void merge(vector<int> a,int start,int mid,int end)
{
	
	int* lf=(int*)malloc(sizeof(int)*(mid-start+1));
	int* rf=(int*)malloc(sizeof(int)*(end-mid));
	
	for(int i=start;i<=mid;i++)
		lf[i-start]=a[i];
	
	for(int i=mid+1;i<=end;i++)
		rf[i-mid-1]=a[i];
	
	int i=start,j=mid+1,k=start;
	
	while(i<=mid && j<=end)
	{
		if(lf[i-start]<rf[j-mid-1])
		{
			a[k++]=lf[i-start];
			i++;
		}
		else
		{
			a[k++]=rf[j-mid-1];
			j++;
		}
	}
	while(i<=mid)
	{
		a[k++]=lf[i-start];
		i++;
	}
	
	while(j<=end)
	{
		a[k++]=rf[j-mid-1];
		j++;
	}
	
}
		
void merge_sort(vector<int> a,int start,int end)
{
	if(start>=end)	return;
	
	int mid=(start+end)/2;
	merge_sort(a,start,mid);
	merge_sort(a,mid+1,end);
	
	merge(a,start,mid,end);
}
bool is_sorted(vector<int> a,int n)
{
	bool inc=1;
	
	int i=0;
	while(i<n-1 && a[i]==a[i+1])
		i++;
	
	if(i==n-1)	return 1;	//all are equal
	
	if(a[i]>a[i+1])
		inc=0;
	
	for(;i<n-1;i++)
	{
		if(inc)
		{
			if(a[i]>a[i+1])
				return 0;
		}
		else
		{
			if(a[i]<a[i+1])
				return 0;
		}
	}
	if(inc)	return 1;
	//to make it inc sort
	for(i=0;i<n/2;i++)
		swap(a[i],a[n-i-1]);
	return 1;
}
	
vector<int> tapes[100005];
int main()
{
	int n_tapes,n_files;
	cout<<"\nEnter number of tapes: ";
	cin>>n_tapes;
	
	cout<<"\nEnter size of each tape: ";
	vector<int> tape_size(n_tapes,0),occupied(n_tapes,0);
	for(int i=0;i<n_tapes;i++)
		cin>>tape_size[i];
		
	cout<<"\nEnter number of files : ";
	cin>>n_files;
	vector<int>files(n_files,0);
	
	cout<<"\nEnter files size :\n";
	for(int i=0;i<n_files;i++)	cin>>files[i];
	if(!is_sorted(files,n_files))
		merge_sort(files,0,n_files-1);
	
	int j=0;
	for(int i=0;i<n_files;i++)
	{
		bool found=0;
		int k=j;
		for( ;k!=j; k=(k+1)%n_tapes)	
		{
			if(occupied[k]+files[i]>tape_size[k])
			{
				found=1;
				break;
			}
		}
		if(!found)	break;
		j=k;
		occupied[j]+=files[i];
		tapes[j].pb(files[i]);
	}
	for(int i=0;i<n_tapes;i++)
	{
		int sum=0,cur=0,ct=0;
		cout<<"\nTAPE "<<i+1<<" : ";
		for(j=0;j<tapes[i].size();j++)
		{
			cout<<tapes[i][j]<<" ";
			cur+=tapes[i][j];
			sum+=cur;
		}
		if(ct!=0)
			cout<<" MRT : "<<fixed<<setprecision(10)<<double(sum)/double(tapes[j].size())<<"\n";
	}
}
	
