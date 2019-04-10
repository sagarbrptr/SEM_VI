#include<bits/stdc++.h>
using namespace std;

struct data
{
	int mn,mx;
	data()
	{
		mn=INT_MIN;
		mx=INT_MAX;
	}
};

data rec(vector<int> a,int start,int end)
{
	data res;
	if(start>end)	
		return res;
	if(start==end)	//one element
	{
		res.mx=a[start];
		res.mn=a[start];
		return res;
	}
	else if(end==start+1)	//two elements
	{
		if(a[start]>a[end])
		{
			res.mx=a[start];
			res.mn=a[end];
		}
		else
		{
			res.mn=a[start];
			res.mx=a[end];
		}
		return res;
	}
	int mid=(start+end)/2;
	data lf=rec(a,start,mid);
	data rf=rec(a,mid+1,end);
	
	if(lf.mx>rf.mx)
		res.mx=lf.mx;
	else
		res.mx=rf.mx;
	
	if(lf.mn<rf.mn)
		res.mn=lf.mn;
	else
		res.mn=rf.mn;
	return res;
}

int main()
{
	int n;
	cout<<"\nEnter number of elements : ";
	cin>>n;
	vector<int>a(n+1,0);
	cout<<"\nEnter N elements : \n";
	for(int i=1;i<=n;i++)
		cin>>a[i];
	
	data res=rec(a,1,n);
	cout<<"\nMinimum element of the array is : "<<res.mn<<"\nMaximum element of the array is : "<<res.mx<<"\n";
}
