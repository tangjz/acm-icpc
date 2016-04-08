#include <cstdio>
#include <cstring>
const int maxn = 20, mod = 1000000007;
int n, x, f[1 << maxn], c[1 << maxn], ans;
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(int x)
{
	if(!x)
	{
		puts("0");
		return;
	}
	int len = 0, buf[8];
	while(x)
	{
		buf[len++] = x % 10;
		x /= 10;
	}
	while(len)
		putchar(buf[--len] + '0');
	putchar('\n');
}
void inc(int &x, int y)
{
    x += y;
    if(x >= mod)
        x -= mod;
}
void dec(int &x, int y)
{
    x -= y;
    if(x < 0)
        x += mod;
}
int mod_pow(int x, unsigned k)
{
    int ret = 1;
    while(k)
    {
        if(k & 1)
            ret = (long long)ret * x % mod;
        x = (long long)x * x % mod;
        k >>= 1;
    }
    return ret;
}
int main()
{
    for(int i = 1; i < maxn; ++i)
        c[i] = c[i >> 1] + (i & 1);
	while(scanf("%d", &n) == 1)
	{
	    memset(f, 0, sizeof f);
    	while(n--)
    	{
    		scan(x);
    		++f[x];
    	}
    	for(int i = 0; i < maxn; ++i)
    		for(int j = 0; j < 1 << maxn; ++j)
    			if(~j & (1 << i))
    				f[j] += f[j | (1 << i)];
    	ans = 0;
    	for(int i = 0; i < maxn; ++i)
        {
            int ret = mod_pow(2, f[i]) - 1;
            if(ret < 0)
                ret += mod;
            if(c[i] & 1)
                dec(ans, ret);
            else
                inc(ans, ret);
        }
        print(ans);
	}
	return 0;
}

