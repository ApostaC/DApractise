#include <stdio.h>
#include <iostream>
#include <algorithm>

#define N 100010
#define MID(a,b)	((a)+(((b)-(a))>>1))

struct Level{
	int val[N];
    int num[N];
};

Level tree[20];		//tree: lvl[0] is original data
int a[N];			//data; assume that there is no duplicates
int n,op;

void buildTree(int l,int r,int lvl)	//update lvl+1 use lvl
{
	if(l==r) return;		//bottom is sorted[]
	int mid=MID(l,r);
	int lp=l,rp=mid+1;
	int midNum=a[mid];

	for(int i=l;i<=r;i++)
	{
		int currVal=tree[lvl].val[i];
		Level & tl=tree[lvl+1];

		if(i==l) tree[lvl].num[i]=0;
		else tree[lvl].num[i] += tree[lvl].num[i-1];

		if(currVal<=midNum)
		{
			tl.val[lp]=currVal;lp++;
			tree[lvl].num[i]++;
			//std::cout<<"lvl: "<<lvl<<" num: "<<currVal<<" toLeft! ( mid and midNum are "<<mid<<" "<<midNum<<")"<<std::endl;
		}
		else
		{
			tl.val[rp]=currVal;rp++;
			//std::cout<<"lvl: "<<lvl<<" num: "<<currVal<<" toRight! ( mid and midNum are "<<mid<<" "<<midNum<<")"<<std::endl;
		}
	}
	buildTree(l,mid,lvl+1);
	buildTree(mid+1,r,lvl+1);
}

int query(int k,int qleft,int qright,int nleft,int nright,int lvl)
{
	Level & tl=tree[lvl];
	if(nleft==nright) return tl.val[nleft];

	int l1=tl.num[qleft-1]-tl.num[nleft-1];	//goto left within range [nleft, qleft-1]
	int l2=tl.num[qright]-tl.num[qleft-1];	//goto left within range [qleft, qright]
	int r1=qleft-nleft-l1;					//goto right within range [nleft,qleft-1]
	int r2=qright-qleft+1-l2;				//goto right within range [qleft,qright]
	
	int mid=MID(nleft,nright);
	if(l2>=k)	//target goto left subtree
	{
		return query(k,nleft+l1,nleft+l1+l2-1,nleft,mid,lvl+1);
	}
	else		//target goto right subtree
	{
		return query(k-l2,mid+1+r1,mid+r1+r2,mid+1,nright,lvl+1);
	}
}

int printTree(int numLvls,int size)
{
	for(int l=0;l<numLvls;l++)
	{
		for(int i=1;i<=size;i++)
			std::cout<<'('<<tree[l].val[i]<<' '<<tree[l].num[i]<<") ";
		std::cout<<std::endl;
	}
}

int main()
{
	std::cin>>n>>op;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		tree[0].val[i]=a[i];
	}
	std::sort(a+1,a+n+1);
//	for(int i=1;i<=n;i++) std::cout<<a[i]<<" ";
//	std::cout<<std::endl;
	buildTree(1,n,0);
//	printTree(4,n);
	int ii,j,k;
	for(int i=0;i<op;i++)
	{
		scanf("%d %d %d",&ii,&j,&k);
		int ret=query(k,ii,j,1,n,0);
		printf("%d\n",ret);
	}
	return 0;
}


