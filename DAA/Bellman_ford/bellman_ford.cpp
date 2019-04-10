#include<bits/stdc++.h>
typedef long long ll;
#define pb push_back
#define INF 10000000000;
using namespace std;

struct edge
{
	ll u,v,w;
};


bool bellman_ford(ll n,ll src,vector<ll> &dist,vector<ll> &parent, vector<edge> g)
{
	dist.resize(n+1);
	parent.resize(n+1);
	for(int i=0;i<=n;i++)	
	{
		dist[i]=INF;
		parent[i]=-1;
	}		
	dist[src]=0;
	for(int i=0;i<n-1;i++)
	{
		bool up=0;
		cout<<"\n\n Iteration : "<<i+1;
		for(auto j:g)
		{
			if(dist[j.v]>dist[j.u]+j.w)
			{
				dist[j.v]=dist[j.u]+j.w;
				parent[j.v]=j.u;
				up=1;
			}
		}
		cout<<"\n Distance : ";
		for(int i=1;i<=n;i++)	cout<<dist[i]<<" ";
		cout<<"\n Parent : ";
		for(int i=1;i<=n;i++)	cout<<parent[i]<<" ";
		if(!up)
			break;
	}
	
	for(auto j:g)
	{
		if(dist[j.v]>dist[j.u]+j.w)
		{
			cout<<"\n Negative Cycle exists!!!";
			return false;
		}
	}
	return true;
}

void print_path(ll n,vector<ll>parent,vector<ll>dist)
{
	cout<<"\n\n Destination\t Path \t Distance\n";
	
	for(int i=1;i<=n;i++)
	{
		cout<<i<<" ";
		stack<ll>s;
		ll x=i;
		while(x!=-1)
		{
			s.push(x);
			x=parent[x];
		}
		while(!s.empty())
		{
			cout<<s.top();
			s.pop();
			if(!s.empty())	cout<<" -> ";
		}
		cout<<"| "<<dist[i]<<"\n";
	}
}
int main()
{
	vector<ll> dist,parent;
	vector< edge> g;
	ll n;
	cout<<"\n Enter number of vertices : ";
	cin>>n;
	int type;
	cout<<"\n Enter 0 for directed graph\n\t 1 for Undirected graph -> ";
	cin>>type;
	
	ll edges;
	cout<<"\n Enter number of edges : ";
	cin>>edges;
	
	cout<<"\n Enter edges in the form (u,v,w) : ";
	
	for(int i=0;i<edges;i++)
	{
		edge e;
		cin>>e.u>>e.v>>e.w;
		g.pb(e);
		if(type)
		{
			swap(e.u,e.v);
			g.pb(e);
		}
	}
	
	ll source;
	cout<<"\nEnter source vertex : ";
	cin>>source;
	
	if(bellman_ford(n,source,dist,parent,g))
	{
		print_path(n,parent,dist);
	}
}
		
