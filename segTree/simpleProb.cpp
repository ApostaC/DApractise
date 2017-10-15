#include <iostream>

#define N 200000
#define LEFT(a) ((a)*2)
#define RIGHT(a) ((a)*2+1)
using namespace std;

int a[N+10];
struct Node{
	long long val;
	long long mark;
	int num;	//number of leaf under this node
};

Node tree[4*N+10];

int n,op;

void buildTree(int curr,int left,int right)
{
	tree[curr].mark=0;
	tree[curr].num=right-left+1;
	if(left == right)	//leaf?
	{
		tree[curr].val=a[left];
		return;
	}
	int mid=(left+right)/2;
	buildTree(LEFT(curr),left,mid);
	buildTree(RIGHT(curr),mid+1,right);
	tree[curr].val=tree[LEFT(curr)].val + tree[RIGHT(curr)].val;	//get sum
}

void pushDown(int curr)
{
	if(tree[curr].num==1) return;
	if(tree[curr].mark!=0)
	{
		Node & cu=tree[curr];
		Node & lt=tree[LEFT(curr)];
		Node & rt=tree[RIGHT(curr)];
		
		lt.mark+=cu.mark;
		rt.mark+=cu.mark;

		lt.val+=(cu.mark*lt.num);
		rt.val+=(cu.mark*rt.num);

		cu.mark=0;
	}
}

long long query(int curr,int lboard,int rboard,int qleft,int qright)
{
	Node & cu=tree[curr];
	if(qright<lboard || qleft>rboard) return 0;	//no intersection
	if(lboard>=qleft && rboard<=qright) return cu.val;
	
	pushDown(curr);

	int mid=(lboard+rboard)/2;
	long long ret=query(LEFT(curr),lboard,mid,qleft,qright)
			+ query(RIGHT(curr),mid+1,rboard,qleft,qright);
	return ret;
}

void update(int curr,int lboard,int rboard,int uleft,int uright,int addMark)
{
	if(uright<lboard || uleft>rboard) return;
	if(uleft<=lboard && uright>=rboard) 
	{
		tree[curr].mark+=addMark;
		tree[curr].val+=(addMark*tree[curr].num);
		return;
	}
	
	pushDown(curr);

	int mid=(lboard+rboard)/2;
	update(LEFT(curr),lboard,mid,uleft,uright,addMark);
	update(RIGHT(curr),mid+1,rboard,uleft,uright,addMark);
	
	tree[curr].val=tree[LEFT(curr)].val+tree[RIGHT(curr)].val;
}

void showTree(int);

void deal()
{
	char c;int n1,n2,n3;
	cin>>c;
	switch(c)
	{
		case 'Q':
			cin>>n1>>n2;
			cout<<query(1,1,n,n1,n2)<<endl;
			break;
		case 'C':
			cin>>n1>>n2>>n3;
			update(1,1,n,n1,n2,n3);
			break;
		case 'S':
			cin>>n1;
			showTree(n1);break;
		default:
			break;
	}
}
ostream & operator<<(ostream & o,Node & n)
{
	o<<"("<<n.mark<<" "<<n.val<<" "<<n.num<<")";
	return o;
}
void showTree(int curr)
{
	int j1=1;
	cout<<tree[curr]<<endl;
	for(int i=1;tree[curr].num>1;i++)
	{
		j1*=2;
		for(int j=1;j<=j1;j++)
			cout<<tree[curr*2+j-1]<<" ";
		cout<<endl;
		curr*=2;
	}
}
int main()
{
	cin>>n>>op;
	for(int i=1;i<=n;i++) cin>>a[i];
	buildTree(1,1,n);
	for(int i=0;i<op;i++) deal();
	return 0;
}
