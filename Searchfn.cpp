#include<bits/stdc++.h>
using namespace std;
int linear(int ar[],int k,int n){
	int i;
	for(i=0;i<n;i++){
		if(ar[i] == k)
			return i;
	}
	return -1;
}
int binary(int ar[],int k,int l,int h){
	int mid;
	while(l<=h){
		mid = l+(h-l)/2;
		if (ar[mid] == k)
			return mid;
		else if (ar[mid] > k)
			h = mid - 1;
		else
			l = mid + 1;
	}
	if(ar[mid] == k)
		return mid;
	else{
		if(ar[mid] > k)
			return mid - 1;
		else
			return mid;
	}
}

int main(){
	return 0;
}