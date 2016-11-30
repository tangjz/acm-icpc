#include <cstdio>
#include <cstring>
const int maxs = 102, maxn = 30, mod = 10000;
struct BigInt
{
	int len, num[maxn];
	void read(int x)
	{
		for(int i = 0; i < len; ++i)
			num[i] = 0;
		for(len = 0; x; ++len, x /= mod)
			num[len] = x % mod;
		if(!len)
			++len;
	}
	void read(const char* ch)
	{
		for(int i = 0; i < len; ++i)
			num[i] = 0;
 		len = 1;
		int k = strlen(ch);
		for(int i = 0; ; ++i)
		{
			if(i * 4 >= k) { len = i; return; }
			int sum = 0;
			for(int j = k - i * 4 < 4 ? k - i * 4 : 4; j; --j)
				sum = (sum << 3) + (sum << 1) + ch[k - i * 4 - j] - '0';
			num[i] = sum;
		}
	}
	void write() const
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%4.4d", num[i]);
	}
	int cmp(const BigInt &x) const
	{
		if(len != x.len)
			return len < x.len;
		for(int i = len - 1; i >= 0; --i)
			if(num[i] != x.num[i])
				return num[i] < x.num[i];
		return -1;
	}
	bool operator < (const BigInt &x) const
	{
		return this -> cmp(x) > 0;
	}
	bool operator <= (const BigInt &x) const
	{
		return this -> cmp(x);
	}
	bool operator > (const BigInt &x) const
	{
		return this -> cmp(x) == 0;
	}
	bool operator >= (const BigInt &x) const
	{
		return this -> cmp(x) <= 0;
	}
	bool operator == (const BigInt &x) const
	{
		return this -> cmp(x) < 0;
	}
	bool operator != (const BigInt &x) const
	{
		return this -> cmp(x) >= 0;
	}
	BigInt operator + (const int &x) const
	{
		BigInt tmp = *this;
		tmp.num[0] += x;
		for(int i = 0; i < tmp.len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
			else
				break;
		while(tmp.num[tmp.len])
		{
			tmp.num[tmp.len + 1] = tmp.num[tmp.len] / mod;
			tmp.num[tmp.len++] %= mod;
		}
		return tmp;
	}
	BigInt operator += (const int &x)
	{
		return *this = *this + x;
	}
	BigInt operator + (const BigInt &x) const
	{
		BigInt tmp = *this;
		if(x.len > len)
			tmp.len = x.len;
		for(int i = 0; i < x.len; ++i)
			tmp.num[i] += x.num[i];
		for(int i = 0; i < tmp.len; ++i)
			if(tmp.num[i] >= mod)
			{
				++tmp.num[i + 1];
				tmp.num[i] %= mod;
			}
		if(tmp.num[tmp.len])
			++tmp.len;
		return tmp;
	}
	BigInt operator += (const BigInt &x)
	{
		return *this = *this + x;
	}
	BigInt operator - (int x) const
	{
		BigInt tmp = *this;
		for(int i = 0; i < len && x; ++i, x /= mod)
		{
			if(tmp.num[i] < x % mod)
			{
				tmp.num[i] += mod;
				--tmp.num[i + 1];
			}
			tmp.num[i] -= x % mod;
		}
		while(!tmp.num[tmp.len - 1] && tmp.len > 1)
			--tmp.len;
		return tmp;
	}
	BigInt operator -= (const int &x)
	{
		return *this = *this - x;
	}
	BigInt operator - (const BigInt &x) const
	{
		BigInt tmp = *this;
		for(int i = 0; i < len; ++i)
		{
			if(tmp.num[i] < x.num[i])
			{
				tmp.num[i] += mod;
				--tmp.num[i + 1];
			}
			tmp.num[i] -= x.num[i];
		}
		while(!tmp.num[tmp.len - 1] && tmp.len > 1)
			--tmp.len;
		return tmp;
	}
	BigInt operator -= (const BigInt &x)
	{
		return *this = *this - x;
	}
	BigInt operator * (int x) const
	{
		BigInt tmp = *this;
		for(int i = 0; i < len; ++i)
			tmp.num[i] *= x;
		for(int i = 0; i < len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		while(tmp.num[tmp.len])
		{
			tmp.num[tmp.len + 1] = tmp.num[tmp.len] / mod;
			tmp.num[tmp.len++] %= mod;
		}
		return tmp;
	}
	BigInt operator *= (const int &x)
	{
		return *this = *this * x;
	}
	BigInt operator * (const BigInt &x) const
	{
		BigInt tmp = {};
		long long sum = 0;
		tmp.len = len + x.len - 1;
		for(int i = 0; i < tmp.len; ++i)
		{
			for(int j = 0; j < len && j <= i; ++j)
				sum += num[j] * x.num[i - j];
			tmp.num[i] = sum % mod;
			sum /= mod;
		}
		while(sum)
		{
			tmp.num[tmp.len++] = sum % mod;
			sum /= mod;
		}
		return tmp;
	}
	BigInt operator *= (const BigInt &x)
	{
		return *this = *this * x;
	}
	BigInt operator / (int x) const
	{
		BigInt tmp = *this;
		for(int i = len - 1; i; --i)
		{
			tmp.num[i - 1] += (tmp.num[i] % x) * mod;
			tmp.num[i] /= x;
		}
		tmp.num[0] /= x;
		while(!tmp.num[tmp.len - 1] && tmp.len > 1)
			--tmp.len;
		return tmp;
	}
	BigInt operator /= (const int &x)
	{
		return *this = *this / x;
	}
	BigInt operator / (const BigInt &x) const
	{
		BigInt ans = {}, tmp = {};
		ans.len = len;
		for(int i = len - 1; i >= 0; --i)
		{
			tmp = tmp * mod + num[i];
			int l = 0, r = mod - 1;
			while(l < r)
			{
				int mid = l + r + 1 >> 1;
				if(x * mid > tmp)
					r = mid - 1;
				else
					l = mid;
			}
			ans.num[i] = l;
			tmp -= x * l;
		}
		while(!ans.num[ans.len - 1] && ans.len > 1)
			--ans.len;
		return ans;
	}
	BigInt operator /= (const BigInt &x)
	{
		return *this = *this / x;
	}
	BigInt sqrt() const
	{
		BigInt L = {}, R = *this, M;
		L.read(0);
		while(L < R)
		{
			M = (L + R) / 2;
			if(M * M < *this)
				L = M + 1;
			else
				R = M;
		}
		return L;
	}
} m, d, n, t, p, q, delta;
int e;
char str1[maxs], str2[maxs];
int main()
{
	for(int Case = 1; scanf("%s%s%d", str1, str2, &e) == 3 && str1[0] && str2[0] && e; ++Case)
	{
		n.read(str1);
		d.read(str2);
		m = d * e - 1;
		for(int i = 1; ; ++i)
		{
			t = m / i;
			if(t >= n)
				continue;
			delta = (n - t - 1) * (n - t - 1);
			if(delta < t * 4)
				continue;
			delta = (delta - t * 4).sqrt();
			p = (n - t - 1 - delta) / 2 + 1;
			q = (n - t - 1 + delta) / 2 + 1;
			if(p * q == n && (p - 1) * (q - 1) == t)
				break;
		}
		printf("Case #%d: ", Case);
		p.write();
		putchar(' ');
		q.write();
		putchar('\n');
	}
	return 0;
}
