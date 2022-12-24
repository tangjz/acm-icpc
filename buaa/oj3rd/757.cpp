#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 51, maxm = 51;
const int Size = maxn * maxn * maxm * maxm;
int t, n, Q[Size + 233], head, tail;
char str[maxn][maxm];
bool vis[Size + 233], flag;
int val(int i, int j, int p, int q)
{
	return ((i * maxn + j) * maxn + p) * maxm + q;
}
void rev(int val, int& i, int &j, int& p, int& q)
{
	q = val % maxm;
	val /= maxm;
	p = val % maxm;
	val /= maxm;
	j = val % maxn;
	val /= maxn;
	i = val;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		flag = 0;
		head = tail = 0;
		memset(vis, 0, sizeof vis);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%s", str[i]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(i != j && str[i][0] == str[j][0])
				{
					int Hash = val(i, j, 0, 0);
					Q[tail++] = Hash;
					vis[Hash] = 1;
				}
		int i, j, p, q;
		while(head < tail)
		{
			rev(Q[head++], i, j, p, q);
			if(str[i][p + 1] == str[j][q + 1])
				if(str[i][p + 1] == '\0')
				{
					flag = 1;
					break;
				}
				else
				{
					int Hash = val(i, j, p + 1, q + 1);
					if(vis[Hash])
						continue;
					Q[tail++] = Hash;
					vis[Hash] = 1;
				}
			else if(str[i][p + 1] == '\0')
			{
				for(int k = 0; k < n; ++k)
					if(str[k][0] == str[j][q + 1])
					{
						int Hash = val(k, j, 0, q + 1);
						if(vis[Hash])
							continue;
						Q[tail++] = Hash;
						vis[Hash] = 1;
					}
			}
			else if(str[j][q + 1] == '\0')
			{
				for(int k = 0; k < n; ++k)
					if(str[i][p + 1] == str[k][0])
					{
						int Hash = val(j, k, p + 1, 0);
						if(vis[Hash])
							continue;
						Q[tail++] = Hash;
						vis[Hash] = 1;
					}
			}
		}
		puts(flag ? "NO" : "YES");
	}
	return 0;
}
