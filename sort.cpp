#include<iostream>
using namespace std;

void insertSort(int *a,int n) {
	int i=0,j=0;
	for(i=1; i<n; ++i) {
		int t=a[i];
		for(j=i-1; j>=0; --j) { //从a[i-1]不断向前找插入位置，一旦当前元素大于等于前面的元素就停止
			if(a[j]>t) {
				a[j+1]=a[j];//大的元素后移
			} else break; //直到找到不大于t的，退出循环
		}
		a[j+1]=t;
	}
}

void quickSort(int *a,int low,int high) {
	int i=low,j=high;
	if(i>=j)return;
	int t=a[i];//枢轴
	while(i<j) {
		while(i<j&&a[j]>=t)j--;
		a[i]=a[j];//比枢轴小的放到前面
		while(i<j&&a[i]<=t)i++;
		a[j]=a[i];//比枢轴大的放到后面
	}
	a[i]=t;//枢轴放到正确
	QuickSort(a,low,i-1);
	QuickSort(a,i+1,high);
}

void selectSort(int *a,int n) {
	for(int i=0; i<n-1; ++i) {
		int min_index=i;
		for(int j=i+1; j<n; ++j) {
			if(a[j]<a[min_index]) { //比较
				min_index=j;
			}
		}
		if(i!=min_index) {
			swap(a[i],a[min_index]);//移动
		}
	}
}

void BubbleSort(int *a,int n) {
	for(int i=0; i<n; ++i) { //i是最前元素
		bool swaped=false;
		for(int j=n-1; j>i; --j) { //每趟把最小元素放到i处
			if(a[j]<a[j-1]) {
				swap(a[j],a[j-1]);
				swaped=true;
			}
		}
		if(swaped==false) {
			break;
		}
	}
}

class HeapSort {
	public:
		void HeapAdjust(int *a,int k,int n) { //调整根为k的树，使元素a[k]到达正确位置
			int t=a[k];
			for(int i=2*k; i<=n; i*=2) {
				if(i<n&&a[i]<a[i+1]) {
					i++;
				}
				if(t>=a[i])break;
				else {
					a[k]=a[i];//将更大的儿子上升
					k=i;//下坠，因为替换可能使子树不满足大根堆性质，需要继续调整
				}
			}
			a[k]=t;//将t放到最终位置
		}
		void BuildMaxHeap(int *a,int n) { //根据原始一维数组构建最大堆
			for(int i=n/2; i>0; --i) { //i从最大分支节点n/2开始调整
				HeapAdjust(a,i,n);
			}
		}

		void HeapSort(int *a,int n) { //注意数组a[0]为空，便于2*i找左儿子
			BuildMaxHeap(a,n);
			for(int i=n; i>1; --i) {
				swap(a[1],a[i]);//将堆顶元素（最大元素）和堆底元素交换
				HeapAdjust(a,1,i-1);//将剩下i-1个元素调整成最大堆
			}
		}
};

class MergeSort {
	public:
		//将a[low,mid]和a[mid+1,high]归并
		void Merge(int *a,int low,int mid,int high) {
			int i,j,k;
			int b[200];
			for(i=low; i<=high; ++i) { //利用b作为辅助空间
				b[i]=a[i];
			}
			for(i=low,j=mid+1,k=i; i<=mid&&j<=high; ++k) {
				if(b[i]<b[j]) { //不断将较小元素复制过来
					a[k]=b[i++];
				} else {
					a[k]=b[j++];
				}
			}
			while(i<=mid) { //将剩余的复制过来
				a[k++]=b[i++];
			}
			while(j<=mid) {
				a[k++]=b[j++];
			}
		}
		void MergeSort(int *a,int low,int high) {
			if(low<high) {
				int mid=(low+high)>>1;
				MergeSort(a,low,mid);//先将左右分别排好序
				MergeSort(a,mid+1,high);
				Merge(a,low,mid,high);//二路归并
			}
		}
};

int main() {
	int a[]= {49,38,65,97,76,13,27,49};
	int n=8;
	insertSort(a,n);
	for(int i=0; i<n; ++i) {
		cout<<a[i]<<' ';
	}

}
