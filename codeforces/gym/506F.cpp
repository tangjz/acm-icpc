#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
const int maxn = 51;
const double eps1 = 1e-8, eps2 = 1e-9;
int t, n;
double w, p, s[maxn];
priority_queue<double, vector<double>, greater<double> > Q;
int dcmp(double x)
{
	if(-eps1 < x && x < eps1)
		return 0;
	return x < 0 ? -1 : 1;
}
bool check()
{
	while(!Q.empty())
		Q.pop();
	for(int i = 0; i <= n; ++i)
		if(dcmp(s[i]) > 0)
			Q.push(s[i]);
	while(!Q.empty())
	{
		double tmp1 = Q.top();
		Q.pop();
		if(Q.empty())
			return dcmp(tmp1 - w) <= 0;
		double tmp2 = Q.top();
		Q.pop();
		Q.push((tmp1 + tmp2) / (1 - p));
	}
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lf%lf%d", &w, &p, &n);
		double l = 0, r = w;
		p /= 100;
		s[0] = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%lf", s + i);
			r -= s[i];
		}
		if(!check())
		{
			puts("-1");
			continue;
		}
		while(r - l >= eps2)
		{
			s[0] = (l + r) / 2;
			if(check())
				l = s[0];
			else
				r = s[0];
		}
		printf("%.8f\n", l);
	}
	return 0; 
}
