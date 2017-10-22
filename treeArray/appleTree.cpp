#include <iostream>
#define MAXN 100010
using namespace std;

int lft[MAXN],rht[MAXN],a[MAXN],c[MAXN];
int key,son[2*MAXN],nex[2*MAXN],map[2*MAXN];
int n,m;

void connect(int a,int b)
{
	int temp=son[a];
	son[a]=b;
	nex[b]=temp;
}
void buildTree()
{
	cin>>n;int a,b;
	for(int i=0;i<n-1;i++) 
	{
		scanf("%d%d",&a,&b);
		connect(a,b);
	}
}

void dfs(int i)
{
	map[i]=key;
	lft[key]=key;
	int j=son[i];
	while(j)
	{
		key+=1;
		dfs(j);
		j=nex[j];
	}
	rht[map[i]]=key;
}

int lowBit(int x)
{
	return x&(-x);
}

int getSum(int k)
{
	int sum=0;
	while(k>=1)
	{
		sum+=c[k];
		k-=lowBit(k);
	}
	return sum;
}

void edit(int k,int num)
{
	while(k<=n)
	{
		c[k]+=num;
		k+=lowBit(k);
	}
}
void printAC();
void operate()
{
	char ch;int id;
	scanf("%c %d%*c",&ch,&id);
	id=map[id];
//	cout<<"ch="<<ch<<endl;
	switch(ch)
	{
		case 'Q':
			printf("%d\n",getSum(rht[id])-getSum(lft[id]-1));
			break;
		case 'C':
			if(a[id]==1) edit(id,-1);
			else edit(id,1);
			a[id]=1-a[id];
			break;
		default:
		//	printAC();
			break;
	}
}	
void printAC()
{
	cout<<"a : ";
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	cout<<endl<<"c : ";
	for(int i=1;i<=n;i++) cout<<c[i]<<" ";
	cout<<endl<<"left : ";
	for(int i=1;i<=n;i++) cout<<lft[i]<<" ";
	cout<<endl<<"right : ";
	for(int i=1;i<=n;i++) cout<<rht[i]<<" ";
	cout<<endl<<"map : ";
	for(int i=1;i<=n;i++) cout<<map[i]<<" ";
	cout<<endl;
}
int main(int argc, char * argv[])
{
	buildTree();
	key=1;dfs(1);
	cin>>m;cin.get();
	for(int i=1;i<=n;i++)
	{
		a[i]=1;
		edit(i,1);
	}
	for(int i=0;i<m;i++)
	{
		operate();
	}
	return 0;
}
