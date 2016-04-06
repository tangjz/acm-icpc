#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50010;
int n, m, pos[maxn], f[maxn], r[maxn], cnt;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", r + i);
	for(int i = 1; i <= n; ++i)
		pos[i] = i;
	for(int i = 0, L = 1, R = n; i < n; ++i)
	{
		int id = L + r[i % m] % (R - L + 1);
		if(pos[id] > cnt + 1)
		{
			f[pos[id]] = R;
			swap(pos[id], pos[L]);
			swap(pos[L], pos[R]);
			--R;
		}
		else
		{
			f[cnt + 1] = L;
			swap(pos[id], pos[L]);
			++L;
			while(cnt < n && f[cnt + 1])
				++cnt;
		}
	}
	for(int i = 1; i <= n; ++i)
		printf("%d\n", f[i]);
	return 0;
}

