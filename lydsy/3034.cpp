/*
 * 答案一定是前i个质数的乘积 先预处理答案 询问直接二分 
 */
#include <cstdio>
#include <cstring>
const int maxn = 3127, mod = 100000000;
char ch[25010];
template<typename _Tp>
inline const _Tp &min(const _Tp &a, const _Tp &b) { return  a < b ? a : b; }
struct Big_int
{
	int len, num[maxn];
	void clear(void) { len = 0; memset(num, 0, sizeof(num)); }
	void getint(const int &x) { num[0] = x; len = 1; }
	void getstring(void)
	{
		scanf("%s", ch);
		for(int i = 0, k = strlen(ch); ; ++i)
		{
			if(i << 3 >= k) { len = i; return; }
			int sum = 0;
			for(int j = min(8, k - (i << 3)); j; --j) sum = (sum << 3) + (sum << 1) + ch[k - (i << 3) - j] - '0';
			num[i] = sum;
		}
	}
	void put(void) const
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i) printf("%8.8d", num[i]);
		putchar('\n');
	}
	int cmp(const Big_int &x) const
	{
		if(len != x.len) return len < x.len;
		for(int i = len - 1; i >= 0; --i) if(num[i] != x.num[i]) return num[i] < x.num[i];
		return -1;
	}
	bool operator < (const Big_int &x) const { return this -> cmp(x) > 0; }
	bool operator <= (const Big_int &x) const { return this -> cmp(x); }
	Big_int operator + (const Big_int &x) const
	{
		Big_int tmp = *this;
		for(int i = 0; i < x.len; ++i) tmp.num[i] += x.num[i];
		for(int i = 0; i < tmp.len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		while(tmp.num[tmp.len])
		{
			if(tmp.num[tmp.len] >= mod)
			{
				tmp.num[tmp.len + 1] = tmp.num[tmp.len] / mod;
				tmp.num[tmp.len] %= mod;
			}
			++tmp.len;
		}
		return tmp;
	}
	Big_int operator += (const Big_int &x) { return *this = *this + x; }
	Big_int operator * (int x) const
	{
		long long cnt = 0;
		Big_int tmp = *this;
		for(int i = 0; i < len; ++i)
		{
			cnt += tmp.num[i] * (long long)x;
			tmp.num[i] = cnt % mod;
			cnt /= mod;
		}
		while(cnt)
		{
			tmp.num[tmp.len++] = cnt % mod;
			cnt /= mod;
		}
		return tmp;
	}
	Big_int operator *= (const int &x) { return *this = *this * x; }
} num[5852], tmp;

const int maxp = 57774;
int tot, prime[maxp];
bool vis[maxp];
int main()
{
	int t;
	for(int i = 2; i < maxp; ++i)
	{
		if(!vis[i]) { vis[i] = 1; prime[tot++] = i; }
		for(int j = 0; j < tot && i * prime[j] < maxp; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
	num[0].getint(2);
	for(int i = 1; i < tot; ++i)
		num[i] = num[i - 1] * prime[i];
	scanf("%d", &t);
	while(t--)
	{
		tmp.getstring();
		int l = 0, r = tot - 1, m;
		while(l < r)
		{
			m = l + r + 1 >> 1;
			if(num[m] <= tmp) l = m;
			else r = m - 1;
		}
		num[l].put();
		tmp.clear();
	}
	return 0;
}
