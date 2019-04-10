#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define f first
#define se second
typedef long long ll;
#define pb push_back

ll n,src;
ll tsp_cost[10][10];
ll red_mat[10][10];

struct term
{
	ll cost;
	vector<ll>path;
	ll mat[10][10];
};
void print_path(term);
//Matrix reduction
ll reduce(ll mat[10][10])
{
	ll cost=0;
	//ROW reduction
	for(int i=1;i<=n;i++)
	{
		ll mn=INF;
		for(int j=1;j<=n;j++)
			mn=min(mn,mat[i][j]);
		if(mn!=INF && mn!=0)
		{
			cost+=mn;
			for(int j=1;j<=n;j++)
				if(mat[i][j]!=INF)
					mat[i][j]-=mn;
		}
	}
	//Column reduction
	for(int i=1;i<=n;i++)
	{
		ll mn=INF;
		for(int j=1;j<=n;j++)
			mn=min(mn,mat[j][i]);
		if(mn!=INF && mn!=0)
		{
			cost+=mn;
			for(int j=1;j<=n;j++)
				if(mat[i][j]!=INF)
					mat[i][j]-=mn;
		}
	}

	return cost;
}

void initialize(ll A[10][10],ll B[10][10])	//matrixA= matrixB
{
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
			A[i][j]=B[i][j];
	}
}
// LCBB required by priority queue
inline bool operator<(const term& lhs, const term& rhs)
{
  return lhs.cost > rhs.cost;
}
priority_queue<term> Q;

void expand(term node)
{
	
		bool visited[n+1];
		ll parent=node.path[node.path.size()-1];	// parent city or last city in the path	
		for(int i=0;i<=n+1;i++)	visited[i]=0;
		for(auto i:node.path)	visited[i]=1;	// all vertices already in path should be marked visited
		ll tempmat[10][10];
		initialize(tempmat,node.mat);
		ll tempcost=node.cost;

		for(int i=1;i<=n;i++)
		{
			if(i==src || visited[i])
				continue;
			term temp_node;
			initialize(red_mat,tempmat);
			
			/* red_mat[i][parent] = INF don't go back to parent 
				Now from parent we have come here at ith so from parent you can't go to any other place 
				red_mat[parent][1:n] = INF
				red_mat[1:n][i] = INF Don't visit i again after wards
			*/

			red_mat[i][parent] = INF;
			for(int j=1;j<=n;j++)
			{	
				red_mat[parent][j]=INF;
				red_mat[j][i]=INF;
			}

			ll cost1 = reduce(red_mat);
			temp_node.cost = tempcost + cost1 + tempmat[parent][i];	
			// cost = C(parent) + reduction cost + c[parent][i]
			temp_node.path = node.path;
			temp_node.path.pb(i);
			initialize(temp_node.mat,red_mat);
			
			//insert temp_node in heap
			Q.push(temp_node);		
		}
		
		
	
}
void print_path(term node)
{
	cout<<node.cost<<"\n";
	for(auto i:node.path)
			cout<<i<<" -> ";
	cout<<src;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cin>>tsp_cost[i][j];	
	}
	cin>>src; 
	initialize(red_mat,tsp_cost);

	term node;
	node.cost = reduce(red_mat);
	node.path.pb(src);	// node will initially have src in the path
	initialize(node.mat,red_mat);
	Q.push(node);

	while(!Q.empty())	//bfs
	{
		node= Q.top();
		Q.pop();
		if(node.path.size()==n)
		{
			print_path(node);
			break;
		}
		expand(node);
	}

}
//Note :  The input matrix must have infinte walue as INF and cost of i to i must be INF as declared above
