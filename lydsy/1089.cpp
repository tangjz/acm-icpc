/*
 * 设在n叉树时不超过i层的树的种类为f[i]
 * 对于由i - 1变到i时，我们新添的根节点要么所有子树都有(共f[i - 1]^n种)
 * 要么一个子树也没有(只有一种)
 * 所以f[i] = f[i - 1] ^ n + 1，ans = f[d] - f[d - 1]
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int mod = 10000;
struct Node
{
	int len, num[60];
	void init() { len = num[0] = 1; }
	Node operator + (const int &x)
	{
		int i = 0;
		num[0] += x;
		while(num[i] >= mod)
		{
			num[i + 1] += num[i] / mod;
			num[i++] %= mod;
		}
		len = max(len, i + 1);
		return *this;
	}
	Node operator += (const int &x) { *this = *this + x; return *this; }
	Node operator - (const Node &x)
	{
		int i;
		for(i = 0; i < len; ++i)
		{
			if(num[i] < x.num[i]) { num[i] += mod; --num[i + 1]; }
			num[i] -= x.num[i];
		}
		while(!num[len - 1] && len > 1) --len;
		return *this;
	}
	Node operator * (const Node &x)
	{
		Node tmp = {};
		int i, j;
		for(i = 0; i < len; ++i)
			for(j = 0; j < x.len; ++j)
			{
				tmp.num[i + j] += num[i] * x.num[j];
				if(tmp.num[i + j] >= mod)
				{
					tmp.num[i + j + 1] += tmp.num[i + j] / mod;
					tmp.num[i + j] %= mod;
				}
			}
		tmp.len = len + x.len - 1;
		for(i = 0; i < tmp.len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		while(tmp.num[tmp.len])
		{
			if(tmp.num[tmp.len] >= mod)
			{
				tmp.num[tmp.len + 1] += tmp.num[tmp.len] / mod;
				tmp.num[tmp.len] %= mod;
			}
			++tmp.len;
		}
		return tmp;
	}
	Node operator *= (const Node &x) { *this = *this * x; return *this; }
	void Print()
	{
	 	 int i;
	 	 printf("%d", num[len - 1]);
	 	 for(i = len - 2; i >= 0; --i) printf("%4.4d", num[i]);
	 	 printf("\n");
	}
} f[17] = {};
int n, d;
int main()
{
	int i, j;
	scanf("%d%d", &n, &d);
	f[0].init();
	for(i = 1; i <= d; ++i)
	{
		j = n;
		Node tmp = f[i - 1];
		f[i].init();
		while(j)
		{
			if(j & 1) f[i] *= tmp;
			if(j != 1) tmp *= tmp;
			j >>= 1;
		}
		f[i] += 1;
	}
	if(d) (f[d] - f[d - 1]).Print();
	else f[d].Print();
	return 0;
}
