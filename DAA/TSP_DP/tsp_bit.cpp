#include<iostream>
using namespace std;

#define INT_MAX 999999

int n=4;
int dist[500][500] = {
        {0,10,15,20},
        {5,0,9,10},
        {6,13,0,12},
        {8,8,9,0}
};
int VISITED_ALL = (1<<n) -1;

int dp[16][4];


int  tsp(int mask,int pos){
	
	if(mask==VISITED_ALL){
		return dist[pos][0];
	}
	if(dp[mask][pos]!=-1){
	   return dp[mask][pos];
	}

	//Now from current node, we will try to go to every other node and take the min ans
	int ans = INT_MAX;

	//Visit all the unvisited cities and take the best route
	for(int city=0;city<n;city++){

		if((mask&(1<<city))==0){

			int newAns = dist[pos][city] + tsp( mask|(1<<city), city);
			ans = min(ans, newAns);
		}

	}
	
	return dp[mask][pos] = ans;
} 
void print(int mask,int pos)
{
	if(mask==VISITED_ALL){
		cout<<" "<<pos<<"-> 0";
		return;
	}
	//Now from current node, we will try to go to every other node and take the min ans
	int ans = INT_MAX,nxt=0;

	//Visit all the unvisited cities and take the best route
	for(int city=0;city<n;city++){

		if((mask&(1<<city))==0){

			int newAns = dist[pos][city] + dp[ mask|(1<<city)][ city];
			if(ans> newAns);
				nxt=city;
		}

	}
	cout<<pos<<" -> ";
	print(mask|1<<nxt,nxt);
}
		
int main(){

    cin>>n;
        /* init the dp array */
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j] = -1;
        }
    }
    for(int i=0;i<n;i++)	for(int j=0;j<n;j++)	cin>>dist[i][j];
	cout<<"Travelling Saleman Distance is "<<tsp(1,0);
	//print(1,0);
return 0;
}

