#include <iostream>
#define N 10000
#define LEFT(a) ((a)*2)
#define RIGHT(a) ((a)*2+1)
#define MID(a,b)	((a)+(((b)-(a))>>1))
using namespace std;

struct Node
{
	int sum;
};

Node tree[N];

int n,a[N];

void buildTree(int l,int r,int curr)
{
	tree[curr].sum=r-l+1;
	if(l==r) return;
	buildTree(l,MID(l,r),LEFT(curr));
	buildTree(MID(l,r)+1,r,RIGHT(curr));
}

int query(int k,int l,int r,int curr)
{
	Node & cu=tree[curr];
	cu.sum--;
	if(l==r) return l;
	int mid=MID(l,r);
	if(k<=tree[LEFT(curr)].sum)
		return query(k,l,mid,LEFT(curr));
	else return query(k-tree[LEFT(curr)].sum,mid+1,r,RIGHT(curr));
}

int ans[N];
int main()
{
	cin>>n;
	for(int i=2;i<=n;i++) cin>>a[i];
	a[1]=0;
	buildTree(1,n,1);
	for(int i=n;i>0;i--) ans[i]=query(a[i]+1,1,n,1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
	return 0;
}
