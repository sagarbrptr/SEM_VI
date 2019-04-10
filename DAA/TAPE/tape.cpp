// Multiple tapes of fixed size
#include<bits/stdc++.h>
using namespace std;

void merge(int arr[], int left, int mid, int right)
{
	int len_left = mid - left + 1;
	int len_right = right - mid;

	int left_arr[len_left], right_arr[len_right];

	for(int i=0;i<len_left;i++)
		left_arr[i] = arr[left + i];

	for (int i = 0; i < len_right; ++i)
		right_arr[i] = arr[mid+1 + i];

	int left_ind=0, right_ind=0;
	int current = left;

	while((left_ind < len_left) && (right_ind < len_right))
	{
		if(left_arr[left_ind] <= right_arr[right_ind])
		{
			arr[current] = left_arr[left_ind];
			left_ind++;
			current++;
		}

		else
		{
			arr[current] = right_arr[right_ind];
			right_ind++;
			current++;
		}
	}

	while(left_ind < len_left)
	{
		arr[current] = left_arr[left_ind];
		left_ind++;
		current++;
	}

	while(right_ind < len_right)
	{
		arr[current] = right_arr[right_ind];
		right_ind++;
		current++;
	}
}

void merge_sort(int arr[],int left, int right)
{
	if(left < right)
	{
		int mid = left + (right-left)/2;

		merge_sort(arr,left,mid);
		merge_sort(arr,mid+1,right);

		merge(arr,left,mid,right);
	}
}

bool is_sorted(int arr[],int n)
{
	bool inc=1;
	
	if(n==1)	return 1;
	
	int i=0;
	
	while(i<n-1 && arr[i]==arr[i+1])
		i++;
		
	if(i==n-1)
		return 1;
		
	if(arr[i]>arr[i+1])
		inc=0;
	
	for(;i<n-1;i++)
	{
		if(inc)
		{
			if(arr[i]>arr[i+1])
				return 0;
		}
		else
		{
			if(arr[i]<arr[i+1])
				return 0;
		}
	}
	
	if(inc==0)
	{
		for(int j=0;j<n/2;j++)
			swap(arr[j],arr[n-j-1]);
	}
	return 1;
}
		
int main()
{
	int n_files;
	cout<<"\nEnter number of files : ";
	cin>>n_files;
	int a[n_files];
	int n_tapes;
	int tape_size=0;
	
	cout<<"\nEnter number of tapes : ";
	cin>>n_tapes;
	int ** tapes=(int **)malloc(sizeof(int*)*n_tapes);	
	int *sum_in_tape=(int*)malloc(sizeof(int)*n_tapes);
	
	cout<<"\nEnter size of tapes : ";
	cin>>tape_size;
	
	for(int i=0;i<n_tapes;i++)
	{
		tapes[i]=(int*) malloc(sizeof(int)*((n_files/n_tapes)+1));
		sum_in_tape[i]=0;
	}
	
	cout<<"\nEnter size of "<<n_files<<" files : \n";
	for(int i=0;i<n_files;i++)
		cin>>a[i];
	
	if(!is_sorted(a,n_files))
	{
		merge_sort(a,0,n_files-1);
	}
	int j=0,ptr=0;
	
	for(int i=0;i<n_files;i++)
	{
		if(sum_in_tape[j]+a[i]>tape_size)
		{
			cout<<"\nInsufficient tape size!!\n";
			break;
		}
		tapes[j][ptr]=a[i];
		sum_in_tape[j]+=a[i];
		j++;
		if(j==n_tapes)
		{
			ptr++;
			j=0;
		}
	}
	
	for(int i=0;i<n_tapes;i++)
	{
		int cur=0,sum=0;
		cout<<"\nTape "<<i+1<<": ";
		int j=0,ct=0;
		for(j=0;j<=ptr;j++)
		{
			if(tapes[i][j]!=0)
			{
				cout<<tapes[i][j]<<" ";
				cur+=tapes[i][j];
				sum+=cur;
				ct++;
			}
			else
				break;
		}
		if(ct!=0)
			cout<<" MRT = "<<fixed<<setprecision(6)<<double(sum)/double(ct);
	}
}		
