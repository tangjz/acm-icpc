#include <cstdio>
#include <algorithm>

using namespace std;

#define N 100000

const double eps=1e-7;
const int inf=0X3FFFFFFF;

int n,m,l,ll,q,p;
pair<int,int> r[N+9],s[N+9],tt,t[N+9];
int y[3*N+9];
long double ans,tmp,x[3*N+9];

bool cmp(pair<int,int> a,pair<int,int> b)
{
	return a.first<b.first;
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i)
    {
        scanf("%d%d",&r[i].second,&r[i].first);
        y[q++]=r[i].first;
    }
    scanf("%d",&m);
    for (int i=0;i<m;++i)
    {
        scanf("%d%d",&s[i].second,&s[i].first);
        y[q++]=s[i].first;
    }
    scanf("%d",&ll);
    for (int i=0;i<ll;++i)
    {
        scanf("%d%d",&tt.second,&tt.first);
        if (r[0].first<=tt.first && tt.first<=r[n-1].first)
        {
        	t[l++]=tt;
			y[q++]=tt.first;
        }
    }
    sort(y,y+q);
    q=unique(y,y+q)-y;
    r[n++]=make_pair(inf,-inf);
    s[m++]=make_pair(inf,+inf);
    ans=1e12;
    for (int i=0;i<q;++i)
    {
        p=0;
        pair<int,int> L,R;
        R=*upper_bound(r,r+n,make_pair(y[i],0),cmp);
        L=*(upper_bound(r,r+n,make_pair(y[i],0),cmp)-1);
        if (L.first==y[i])
        {
            x[p++]=L.second;
        }
        else
        {
            x[p++]=(long long)(R.second-L.second)*(y[i]-L.first)/(long double)(R.first-L.first)+L.second;
        }

        R=*upper_bound(s,s+m,make_pair(y[i],0),cmp);
        L=*(upper_bound(s,s+m,make_pair(y[i],0),cmp)-1);
        if (L.first==y[i])
        {
            x[p++]=L.second;
        }
        else
        {
            x[p++]=(long long)(R.second-L.second)*(y[i]-L.first)/(long double)(R.first-L.first)+L.second;
        }

        pair<pair<int,int>*,pair<int,int>*> rng=equal_range(t,t+l,make_pair(y[i],0),cmp);
        for (pair<int,int>* j=rng.first;j<rng.second;++j)
        {
        	if (x[0]-eps<j->second && j->second<x[1]+eps)
				x[p++]=j->second;
        }
        sort(x,x+p);
        //printf("%d %d\n",y[i],p);
        //for (int j=0;j<p;++j) printf("%f ",(double)x[j]);puts("");
        tmp=0.0;
        for (int j=1;j<p;++j) tmp=max(tmp,x[j]-x[j-1]);
        ans=min(ans,tmp);
    }
    printf("%.8f\n",(double)ans);
    return 0;
}
