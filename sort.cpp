#include<bits/stdc++.h>
using namespace std;

void ins_sort(int ar[],int n){
	int i,j;
	for(i = 0;i < n - 1;i++){
		for(j = i + 1;j;j--){
			if(ar[j] <= ar[j - 1]){
				ar[j] = ar[j-1] + ar[j];
				ar[j - 1] = ar[j] - ar[j-1];
				ar[j] = ar[j] - ar[j-1];	
			}
			else
				break;
		}
	}
}

void sel_sort(int ar[],int n){
	int i,j,min_val;
	for(i = 0;i < n;i++){
		min_val = i;
		for(j = i + 1;j < n;j++){
			if(ar[j] < ar[min_val])
				min_val = j;
		}
		if(min_val != i){
			ar[min_val] = ar[i] + ar[min_val];
			ar[i] = ar[min_val] - ar[i];
			ar[min_val] = ar[min_val] - ar[i];
		}
	}
}

void bubl_sort(int ar[],int n){
	int i,j,min_val;
	for(i = 0;i < n;i++){
		for(j = 0;j < n-i-1;j++){
			if(ar[j] > ar[j+1]){
				ar[j] = ar[j+1] + ar[j];
				ar[j + 1] = ar[j] - ar[j + 1];
				ar[j] = ar[j] - ar[j + 1];	
			}
		}
	}
}

void merge(int ar[],int l,int m,int h){
	int lar[m - l + 1];
	int rar[h - m];
	int lind,rind,x;

	for(lind=0,x=l;lind < m-l+1;lind++,x++)
		lar[lind] = ar[x];
	
	for(rind = 0;rind < h-m;rind++,x++)
		rar[rind] = ar[x];

	for(x = l, rind = 0, lind = 0; lind < m - l + 1 && rind < h - m;x++){
		if(lar[lind] < rar[rind]){
			ar[x] = lar[lind];
			lind++;
		}
		else {
			ar[x] = rar[rind];
			rind++;
		}
	}

	while(lind < m - l + 1){
		ar[x] = lar[lind];
		lind++;
		x++;
	}
	while(rind < h - m){
		ar[x] = rar[rind];
		rind++;
		x++;
	}
}

void merge_sort(int ar[],int l,int h){
	if(l >= h)
		return;
	int m = l + (h-l)/2;
	merge_sort(ar,l,m);
	merge_sort(ar,m+1,h);
	merge(ar,l,m,h);
}

int piv(int ar[],int l,int h){
	int xch,i;

	for(i=l+1,xch=l+1;i<=h;i++){
		if(ar[i] <= ar[l]){
			if(xch != i){
				ar[xch] = ar[xch] + ar[i];
				ar[i] = ar[xch] - ar[i];
				ar[xch] = ar[xch] - ar[i];
			}
			xch++;
		}
	}
	xch--;
	if(xch != l){
		ar[xch] = ar[xch] + ar[l];
		ar[l] = ar[xch] - ar[l];
 		ar[xch] = ar[xch] - ar[l];	
	}
	return xch;
}

void q_sort(int ar[],int l,int h){
	if(l >= h)
		return;
	int pivot = piv(ar,l,h);
	q_sort(ar,l,pivot - 1);
	q_sort(ar,pivot + 1,h);

}
void heapify(int heap[],int i,int size){
	int l,r,max;
	l = 2*i+1;
	r = 2*i+2;
	
	while(i < size){
		max = i;

		if(l < size && heap[max] < heap[l])
			max = l;
		if(r < size && heap[max] < heap[r])
			max = r;
		if(max != i){
			heap[max] = heap[max] + heap[i];
			heap[i] = heap[max] - heap[i];
 			heap[max] = heap[max] - heap[i];	
			i = max;
			l = 2*i+1;
			r = 2*i+2;
		}
		else
			break;
	}

}
void buildheap(int heap[],int size){
	int i;
	for(i = size/2 ; i > -1 ;i--)
		heapify(heap,i,size);
}
int extractmax(int heap[],int* size){
	if(*size){
		int max = heap[0];
		heap[0] = heap[*size - 1];
		*size = *size - 1;
		heapify(heap,0,*size);
		return max;
	}
	return -1;
}
void heapsort(int heap[],int size){
	buildheap(heap,size);
	int max,i;
	for(i=size - 1;i > -1;i--){
		max = extractmax(heap,&size);
		heap[i] = max;
	}
}
int main(){
	int i,n,t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int ar[n];
		for(i=0;i<n;i++)
			scanf("%d",&ar[i]);
		int key;
		/*bubl_sort(ar,n);
		sel_sort(ar,n);
		ins_sort(ar,n);*/
		//merge_sort(ar,0,n-1);
		//q_sort(ar,0,n-1);
		heapsort(ar,n);
		for(i=0;i<n;i++)
			printf("%d ",ar[i]);
		printf("\n");
	}
	return 0;
}