#include <iostream>
#include <algorithm>

using namespace std;

#define L 100000
#define N 500

struct Seg{int l,r,m,mrk;}S[4*L+9];
struct Rect{int x,y,p,q;}r[N+9];

int T,n,d;

bool cmpx(Rect a,Rect b)
{
	return a.x<b.x;
}
bool cmpy(Rect a,Rect b)
{
	return a.y<b.y;
}
void con(int k,int l,int r)
{
	S[k].l=l,S[k].r=r,S[k].mrk=0;
	if (l==r) S[k].m=0;
	else
	{
		con(2*k+1,l,(l+r)/2);
		con(2*k+2,(l+r)/2+1,r);
		S[k].m=max(S[2*k+1].m,S[2*k+2].m);
	}
}
void upd(int k,int l,int r,int v)
{
	if (l<=S[k].l && S[k].r<=r)
	{
		S[k].m=v;
		S[k].mrk=v;
	}
	else
	{
		if (S[k].mrk)
		{
			int &tmp=S[k].mrk;
			S[2*k+1].m=tmp;
			S[2*k+1].mrk=tmp;
			S[2*k+2].m=tmp;
			S[2*k+2].mrk=tmp;
			tmp=0;
		}
		int m=(S[k].l+S[k].r)/2;
		if (l<=m) upd(2*k+1,l,r,v);
		if (r>m) upd(2*k+2,l,r,v);
		S[k].m=max(S[2*k+1].m,S[2*k+2].m);
	}
}
int que(int k,int l,int r)
{
	//cout<<S[k].l<<' '<<S[k].r<<endl;
	if (l<=S[k].l && S[k].r<=r)
	{
		return S[k].m;
	}
	else
	{
		if (S[k].mrk)
		{
			int &tmp=S[k].mrk;
			S[2*k+1].m=tmp;
			S[2*k+1].mrk=tmp;
			S[2*k+2].m=tmp;
			S[2*k+2].mrk=tmp;
			tmp=0;
		}
		int m=(S[k].l+S[k].r)/2,ret=0;
		if (l<=m) ret=max(ret,que(2*k+1,l,r));
		if (r>m) ret=max(ret,que(2*k+2,l,r));
		return ret;
	}
}
int main()
{
	cin>>T;
	while (T--)
	{
		cin>>n;
		for (int i=0;i<n;++i)
		{
			cin>>r[i].x>>r[i].y>>r[i].p>>r[i].q;
			--r[i].p,--r[i].q;
		}
		bool flag=true;
		do
		{
			flag=false;

			con(0,0,L);
			sort(r,r+n,cmpy);
			for (int i=0;i<n;++i)
			{
				d=r[i].y-que(0,r[i].x,r[i].p)-1;
				flag|=d;
				r[i].y-=d,r[i].q-=d;
				upd(0,r[i].x,r[i].p,r[i].q);
			}
			con(0,0,L);
			sort(r,r+n,cmpx);
			for (int i=0;i<n;++i)
			{
				d=r[i].x-que(0,r[i].y,r[i].q)-1;
				flag|=d;
				r[i].x-=d,r[i].p-=d;
				upd(0,r[i].y,r[i].q,r[i].p);
			}
		} while (flag);
		int w=0,h=0;
		for (int i=0;i<n;++i)
		{
			w=max(w,r[i].p);
			h=max(h,r[i].q);
		}
		cout<<w<<' '<<h<<endl;
	}
	return 0;
}
