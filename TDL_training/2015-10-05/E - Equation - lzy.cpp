#include <cctype>
#include <cstdio>
#include <cstdlib>

typedef long long i64;

struct Frac{i64 p,q;};

const Frac mul={0,0};
const Frac wng={1,0};
const Frac zro={0,1};

template <typename any> any abs(any x)
{
	return x<0?-x:x;
}
i64 gcd(i64 a,i64 b)
{
	a=abs(a);b=abs(b);
	for (i64 c;b;c=a%b,a=b,b=c);
	return a;
}
Frac operator ~(Frac x)
{
	if (x.p==0 && x.q==0) return x;
	if (x.p==0) x.q=1;
	if (x.q==0) x.p=1;
	i64 g=gcd(x.p,x.q);
	x.p/=g;
	x.q/=g;
	if (x.q<0)
	{
		x.p=-x.p;
		x.q=-x.q;
	}
	return x;
}
bool operator <(Frac x,Frac y)
{
	i64 g=gcd(x.q,y.q);
	return y.q/g*x.p<x.q/g*y.p;
}
bool operator ==(Frac x,Frac y)
{
	return (x.p==y.p)&&(x.q==y.q);
}
bool operator !=(Frac x,Frac y)
{
	return (x.p!=y.p)||(x.q!=y.q);
}
Frac operator +(Frac a,Frac b)
{
	i64 g=gcd(a.q,b.q);
	Frac x;
	x.p=a.p*(b.q/g)+b.p*(a.q/g);
	x.q=a.q/g*b.q;
	return ~x;
}
Frac operator -(Frac a,Frac b)
{
	i64 g=gcd(a.q,b.q);
	Frac x;
	x.p=a.p*(b.q/g)-b.p*(a.q/g);
	x.q=a.q/g*b.q;
	return ~x;
}
Frac operator *(Frac a,Frac b)
{
	Frac x={a.p*b.p,a.q*b.q};
	return ~x;
}
Frac operator /(Frac a,Frac b)
{
	Frac x={a.p*b.q,a.q*b.p};
	return ~x;
}
int x,c,t[32];
int s[32],p;
int n,l[32],r[32];
Frac v[32];

bool isopt(int c)
{
	return c=='+' || c=='-' || c=='*' || c=='/';
}

Frac calc(int opt,Frac a,Frac b)
{
	if (a==wng || b==wng) return wng;
	if (opt=='+') return a+b;
	if (opt=='-') return a-b;
	if (opt=='*') return a*b;
	if (opt=='/') return a/b;
	return wng;
}
Frac linv(int opt,Frac a,Frac b)
{
	if (a==wng || b==wng) return wng;
	if (opt=='+') return a-b;
	if (opt=='-') return a+b;
	if (opt=='*')
	{
		if (b==zro && a!=zro) return wng;
		return a/b;
	}
	if (opt=='/') return a*b;
	return wng;
}
Frac rinv(int opt,Frac a,Frac b)
{
	if (a==wng || b==wng) return wng;
	if (opt=='+') return a-b;
	if (opt=='-') return b-a;
	if (opt=='*')
	{
		if (b==zro && a!=zro) return wng;
		return a/b;
	}
	if (opt=='/')
	{
		if (b==zro && a!=zro) return wng;
		return b/a;
	}
	return wng;
}
void dfs(int k)
{
	//printf("%d\n",k);
	if (isopt(t[k]))
	{
		dfs(l[k]);
		dfs(r[k]);
		if (v[l[k]]!=wng && v[r[k]]!=wng)
			v[k]=calc(t[k],v[l[k]],v[r[k]]);
	}
}
void bfs(int k)
{
	if (isopt(t[k]))
	{
		if (v[l[k]]==wng)
		{
			v[l[k]]=linv(t[k],v[k],v[r[k]]);
			if (v[l[k]]==wng)
			{
				puts("NONE");
				exit(0);
			}
			if (v[l[k]]==mul)
			{
				puts("MULTIPLE");
				exit(0);
			}
			bfs(l[k]);
		}
		if (v[r[k]]==wng)
		{
			v[r[k]]=rinv(t[k],v[k],v[l[k]]);
			if (v[r[k]]==wng)
			{
				puts("NONE");
				exit(0);
			}
			if (v[r[k]]==mul)
			{
				puts("MULTIPLE");
				exit(0);
			}
			bfs(r[k]);
		}
	}
}
int main()
{
	while ((c=getchar())!='\n')
	{
		if (c==' ') continue;
		if (c=='X')
		{
			x=++n;
			t[n]=c;
			v[n]=wng;
			s[p++]=n;
		}
		else if (isdigit(c))
		{
			++n;
			t[n]=c;
			v[n]=(Frac){c-'0',1};
			s[p++]=n;
		}
		else if (isopt(c))
		{
			++n;
			t[n]=c;
			v[n]=wng;
			r[n]=s[--p];
			l[n]=s[--p];
			s[p++]=n;
		}
	}
	dfs(n);
	if (x==0)
	{
		if (v[n]==zro) puts("MULTIPLE");
		else puts("NONE");
		return 0;
	}
	v[n]=zro;
	//for (int i=1;i<=n;++i) printf("%lld/%lld ",v[i].p,v[i].q);putchar('\n');
	bfs(n);
	//for (int i=1;i<=n;++i) printf("%lld/%lld ",v[i].p,v[i].q);putchar('\n');
	if (v[x]==wng) puts("NONE");
	else if (v[x]==mul) puts("MULTIPLE");
	else printf("X = %lld/%lld\n",v[x].p,v[x].q);
	return 0;
}
