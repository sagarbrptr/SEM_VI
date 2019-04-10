#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define f first
#define se second
#define ios ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(v) (v).begin(),(v).end()
typedef long long ll ;
typedef long double ld ;
typedef long long int lli;

using namespace std;
ll ans=0;
int n;
void print(int col[])
{
	ans++;
	cout<<"Solution no. "<<ans<<"\n\t";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(col[i]==j)	cout<<"Q ";
			else	cout<<0<<" ";
		}
		cout<<"\n\t";
	}
	cout<<"\n";
}
bool place(int r,int c,int col[])
{
	for(int i=0;i<r;i++)
	{
		if(col[i]==c || abs(col[i]-c)==(r-i))
			return false;
	}
	return true;
}
bool rec(int row,int col[])
{
	if(row==n)
	{
		print(col);
		return true;
	}
	bool res=0;
	for(int j=0;j<n;j++)
	{
		if(place(row,j,col))
		{
			col[row]=j;
			res|=rec(row+1,col);
			col[row]=-1;
		}
	}
	return res;
}	
			
	
int main()
{
	cin>>n;
	int col[n];
	for(int i=0;i<n;i++)	col[i]=-1;
	rec(0,col);	
		
}
