#include<bits/stdc++.h>
using namespace std;
#define INF 1000000007
#define f first
#define se second
typedef long long ll;
#define pb push_back

map<pair<ll,set<ll>>,ll>g;
ll c[105][105];
ll n,src;

ll dist(ll cur_src,set<ll>s)
{
	if(s.size()==0)	//g(vi,phi) =c[vi][src]
	{
		g[{cur_src,s}]=c[cur_src][src];
		return g[{cur_src,s}];
	}
	if(g.find({cur_src,s})!=g.end())	return g[{cur_src,s}];
	
	ll mn=LLONG_MAX;
	
	for(auto i:s)
	{
		set<ll> temp=s;
		temp.erase(i);
		ll d=c[cur_src][i] + dist(i,temp);
		if(mn>d)
		{
			mn=d;
		}
	}
	
	g[{cur_src,s}]=mn;
	return g[{cur_src,s}];
}
void print_path(ll cur_src,set<ll> s)
{
	ll mn=LLONG_MAX,nxt=src;
	ll mni=src;
	for(auto i:s)
	{
		set<ll> temp=s;
		temp.erase(i);
		if(mn>g[{cur_src,temp}])
		{
			mn=g[{cur_src,temp}];
			nxt=i;
		}
	}
	if(nxt==src)
	{
		cout<<src<<" ";
		return;
	}
	cout<<nxt<<" -> ";
	s.erase(nxt);
	print_path(nxt,s);

}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cin>>c[i][j];	
	}
	cin>>src; 
	set<ll>s;
	for(ll i=1;i<=n;i++)
	{
		if(i!=src)
			s.insert(i);
	}
	cout<<dist(src,s)<<"\n\n";
	cout<<"Path : \n";
	for(int i=1;i<=n;i++)
	{
		if(i!=src)
			s.insert(i);
	}
	cout<<"\n\t"<<src<<" -> ";
	print_path(src,s);
	
}

