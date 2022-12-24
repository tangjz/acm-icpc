#include <cstdio>
template<typename _> inline const _& max(const _& x, const _& y) { return y < x ? x : y; }
const int maxn = 20, mod = 100000;
struct Big_int
{
	int len, num[maxn];
	void init(const int &x)
	{
		num[0] = x % mod;
		num[1] = x / mod;
		while(num[len])
		{
			num[len + 1] += num[len] / mod;
			num[len++] %= mod;
		}
	}
	bool operator < (const Big_int &x) const
	{
		if(len != x.len) return len < x.len;
		for(int i = len - 1; i >= 0; --i) if(num[i] != x.num[i]) return num[i] < x.num[i];
		return true;
	}
	Big_int operator + (const Big_int &x) const
	{
		Big_int tmp = *this;
		tmp.len = max(len, x.len);
		for(int i = 0; i < tmp.len; ++i)
		{
			tmp.num[i] += x.num[i];
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		}
		while(tmp.num[tmp.len])
		{
			tmp.num[tmp.len + 1] += tmp.num[tmp.len] / mod;
			tmp.num[tmp.len++] %= mod;
		}
		return tmp;
	}
	Big_int operator += (const Big_int &x) { return *this = *this + x; }
	Big_int operator * (const int &x) const
	{
		int i;
		Big_int tmp = *this;
		for(i = 0; i < tmp.len; ++i) tmp.num[i] *= x;
		for(i = 0; i < tmp.len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		while(tmp.num[tmp.len])
		{
			tmp.num[tmp.len + 1] += tmp.num[tmp.len] / mod;
			tmp.num[tmp.len++] %= mod;
		}
		return tmp;
	}
	void Print()
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i) printf("%5.5d", num[i]);
		printf("\n");
	}
} pre[81], ans;
int n, m, num[81];
int main()
{
	int i, j, k;
	scanf("%d%d", &n, &m);
	pre[0].init(1);
	for(i = 1; i <= m; ++i) pre[i] = pre[i - 1] * 2;
	while(n--)
	{
        Big_int f[81][81] = {};
		for(i = 1; i <= m; ++i) scanf("%d", &num[i]);
		for(i = 1; i <= m; ++i)
			for(j = 0; j <= i; ++j)
			{
				if(i > j) f[i][j] = max(f[i][j], f[i - 1][j] + pre[i] * num[m - i + j + 1]);
				if(j >= 1) f[i][j] = max(f[i][j], f[i - 1][j - 1] + pre[i] * num[j]);
			}
        Big_int temp = {};
		for(i = 0; i <= m; ++i) temp = max(temp, f[m][i]);
		ans += temp;
	}
	ans.Print();
}