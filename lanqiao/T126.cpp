#include <cstdio>
#include <cstring>
template<typename _> inline const _& min(const _& x, const _& y) { return x < y ? x : y; }
const int maxn = 510, mod = 10000;
char ch[1010];
struct Big_int
{
	int len, num[maxn];
	void getstring(void)
	{
		scanf("%s", ch);
		for(int i(0), k(strlen(ch)); ; ++i)
		{
			if(i << 2 >= k) { len = i; return; }
			int sum(0);
			for(int j = min(4, k - (i << 2)); j; --j) sum = (sum << 3) + (sum << 1) + ch[k - (i << 2) - j] - '0';
			num[i] = sum;
		}
	}
	void put(void) const
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i) printf("%4.4d", num[i]);
		putchar('\n');
	}
	int cmp(const Big_int &x) const
	{
		if(len != x.len) return len < x.len;
		for(int i = len - 1; i >= 0; --i) if(num[i] != x.num[i]) return num[i] < x.num[i];
		return -1;
	}
	bool operator < (const Big_int &x) const { return this -> cmp(x) == 1; }
	Big_int operator + (const Big_int &x) const
	{
		Big_int tmp = *this;
		if(x.len > len) tmp.len = x.len;
		for(int i = 0; i < x.len; ++i) tmp.num[i] += x.num[i];
		for(int i = 0; i < tmp.len; ++i) if(tmp.num[i] >= mod) { ++tmp.num[i + 1]; tmp.num[i] %= mod; }
		if(tmp.num[tmp.len]) ++tmp.len;
		return tmp;
	}
	Big_int operator + (const int &x) const
	{
		Big_int tmp(*this); tmp.num[0] += x;
		for(int i(0); i < len && tmp.num[i] >= mod; ++i) { ++tmp.num[i + 1]; tmp.num[i] -= mod; }
		if(tmp.num[tmp.len]) ++tmp.len;
		return tmp;
	}
	Big_int operator - (const int &x) const
	{
		Big_int tmp(*this); tmp.num[0] -= x;
		for(int i(0); i < len && tmp.num[i] < 0; ++i) { --tmp.num[i + 1]; tmp.num[i] += mod; }
		if(!tmp.num[tmp.len - 1]) --tmp.len;
		return tmp;
	}
	Big_int operator * (const Big_int &x) const
	{
		Big_int tmp = {};
		if(len == 1 && !num[0] || x.len == 1 && !x.num[0]) { tmp.len = 1; return tmp; }
		tmp.len = len + x.len - 1;
		for(int i = 0; i < len; ++i)
			for(int j = 0; j < x.len; ++j)
			{
				tmp.num[i + j] += num[i] * x.num[j];
				if(tmp.num[i + j] >= mod) { tmp.num[i + j + 1] += tmp.num[i + j] / mod; tmp.num[i + j] %= mod; }
			}
		while(tmp.num[tmp.len]) { tmp.num[tmp.len + 1] = tmp.num[tmp.len] / mod; tmp.num[tmp.len++] %= mod; }
		return tmp;
	}
	Big_int operator / (int x) const
	{
		Big_int tmp = *this;
		for(int i = len - 1; i; --i) { tmp.num[i - 1] += (tmp.num[i] % x) * mod; tmp.num[i] /= x; } tmp.num[0] /= x;
		while(!tmp.num[tmp.len - 1] && tmp.len > 1) --tmp.len;
		return tmp;
	}
	Big_int sqrt(void) const
	{
		Big_int l = {}, r, mid;
		l.num[0] = l.len = 1; r = *this;
		while(l < r)
		{
			mid = (l + r + 1) / 2;
			*this < mid * mid ? r = mid - 1 : l = mid;
		}
		return l;
	}
};
Big_int a, b;
int main()
{
	a.getstring();
	b.getstring();
	(a.sqrt() * b.sqrt()).put();
	return 0;
}
