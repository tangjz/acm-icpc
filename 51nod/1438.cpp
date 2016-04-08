#include <set>
#include <cmath>
#include <cstdio>
using namespace std;
const int maxn = 65;
typedef long long LL;
int n;
LL mat[maxn][maxn], row[maxn], col[maxn], last = 1;
set<LL> vis, vis_rc;
int main()
{
	scanf("%d", &n);
	if(n == 1)
	{
		puts("No Solution");
		return 0;
	}
	for(int i = 1; i < n; ++i)
	{
		for(int j = 1; j < n; ++j)
		{
			while(vis.count(last))
				++last;
			mat[i][j] = last;
			row[i] += mat[i][j];
			col[j] += mat[i][j];
			vis.insert(mat[i][j]);
		}
		for(LL k = (LL)sqrt(row[i] + 1.0); ; ++k)
			if(!vis_rc.count(k * k) && k * k > row[i] && !vis.count(k * k - row[i]))
			{
				while(vis.count(last))
					++last;
				mat[i][n] = k * k - row[i];
				row[i] += mat[i][n];
				col[n] += mat[i][n];
				vis.insert(mat[i][n]);
				break;
			}
		vis_rc.insert(row[i]);
	}
	for(int i = 1; i < n; ++i)
	{
		for(LL k = (LL)sqrt(col[i] + 1.0); ; ++k)
			if(!vis_rc.count(k * k) && k * k > col[i] && !vis.count(k * k - col[i]))
			{
				mat[n][i] = k * k - col[i];
				row[n] += mat[n][i];
				col[i] += mat[n][i];
				vis.insert(mat[n][i]);
				break;
			}
		vis_rc.insert(col[i]);
	}
	bool flag = 0;
	while(!flag)
	{
		for(LL k = (LL)sqrt(col[n] + 1.0), d = row[n] - col[n]; 2 * k + 1 <= d; ++k)
			if(!vis_rc.count(k * k) && k * k > col[n] && !vis.count(k * k - col[n]))
			{
				LL kk = (LL)sqrt(k * k + d);
				if(kk * kk < k * k + d)
					++kk;
				if(kk * kk == k * k + d && !vis_rc.count(kk * kk))
				{
					mat[n][n] = k * k - col[n];
					row[n] = kk * kk;
					col[n] = k * k;
					vis.insert(mat[n][n]);
					vis_rc.insert(row[n]);
					vis_rc.insert(col[n]);
					flag = 1;
					break;
				}
			}
		if(!flag)
		{
			vis.erase(mat[n][n - 1]);
			vis_rc.erase(col[n - 1]);
			for(LL k = (LL)sqrt(col[n - 1] + 1.0); ; ++k)
				if(!vis_rc.count(k * k) && k * k > col[n - 1] && !vis.count(k * k - col[n - 1] + mat[n][n - 1]))
				{
					mat[n][n - 1] += k * k - col[n - 1];
					row[n] += k * k - col[n - 1];
					col[n - 1] = k * k;
					break;
				}
			vis.insert(mat[n][n - 1]);
			vis_rc.insert(col[n - 1]);
		}
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			printf("%lld%c", mat[i][j], " \n"[j == n]);
	return 0;
}
