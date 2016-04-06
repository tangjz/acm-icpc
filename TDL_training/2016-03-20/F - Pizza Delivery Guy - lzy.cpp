#include <cstdio>
#include <algorithm>

using namespace std;

int T,n,m,s,o[29],a[29],b[29],c[29],d[29][29],e[29],f[29][29];
int ans;

bool cmp(int x,int y)
{
	return a[x]>a[y];
}

void dfs(int _k)
{
	if (m>=ans) return;
	if (_k==n) {
		ans=m;
		for (int i=0;i<m;++i) {
			e[i]=c[i];
			for (int j=0;j<c[i];++j)
				f[i][j]=d[i][j];
		}
		return;
	}
	int k=o[_k];
	for (int i=0;i<m;++i) {
		if (b[i]+a[k]<=s) {
			b[i]+=a[k];
			d[i][c[i]++]=k;
			dfs(_k+1);
			--c[i];
			b[i]-=a[k];
		}
	}
	b[m]=a[k];
	c[m]=0;
	d[m][c[m]++]=k;
	++m;
	dfs(_k+1);
	--m;
}

int main()
{
	scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&s);
		for (int i=0;i<n;++i) {
			o[i]=i;
			scanf("%d",a+i);
		}
		sort(o,o+n,cmp);
		ans=n+1;
		m=0;
		dfs(0);
		printf("%d\n",ans);
		for (int i=0;i<ans;++i) {
			printf("%d",e[i]);
			for (int j=0;j<e[i];++j)
				printf(" %d",f[i][j]+1);
			putchar('\n');
		}
	}
	return 0;
}
/*
 20 20
 1 2 3 4 5 6 7 8 9 10 11 11 12 12 13 13 14 14 15 15
 20 20
 1 1 2 2 3 3 4 4  5 5 11 11 12 12 13 13 14 14 15 15
*/
