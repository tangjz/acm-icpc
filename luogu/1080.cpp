#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 10000;
struct Big_int
{
	int len, num[1024];
	Big_int(void) { len = 1; memset(num, 0, sizeof num); }
	Big_int(int x) { len = 1; memset(num, 0, sizeof num); num[0] = x; }
	bool operator < (const Big_int &x) const
	{
		if(len != x.len) return len < x.len;
		for(int i = len - 1; i >= 0; --i)
			if(num[i] < x.num[i]) return true;
		return false;
	}
	Big_int operator * (const int &x) const
	{
		Big_int temp = *this;
		for(int i = 0; i < len; ++i) temp.num[i] *=  x;
		for(int i = 0; i < len; ++i)
			if(temp.num[i] >= mod)
			{
				temp.num[i + 1] += temp.num[i] / mod;
				temp.num[i] %= mod;
			}
		while(temp.num[temp.len])
		{
			temp.num[temp.len + 1] += temp.num[temp.len] / mod;
			temp.num[temp.len++] %= mod;
		}
		return temp;
	}
	Big_int operator *= (const int &x) { return *this = *this * x; }
	Big_int operator / (const int &x) const
	{
		Big_int temp = *this;
		for(int i = len - 1; i; --i)
		{
			temp.num[i - 1] += (temp.num[i] % x) * mod;
			temp.num[i] /= x;
		}
		temp.num[0] /= x;
		while(!temp.num[temp.len - 1] && temp.len > 1) --temp.len;
		return temp;
	}
	void Print()
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i) printf("%4.4d", num[i]);
		putchar('\n');
	}
} ans, sum, tmp;
struct Node { int a, b; } game[1001];
bool cmp(const Node &x, const Node &y) { return x.a * x.b < y.a * y.b; }
int n;
int main()
{
	int i;
	scanf("%d", &n);
	scanf("%d", &i);
	sum = i;
	scanf("%d", &i);
	for(i = 0; i < n; ++i) scanf("%d%d", &game[i].a, &game[i].b);
	sort(game, game + n, cmp);
	for(i = 0; i < n; ++i)
	{
		tmp = sum / game[i].b;
		if(ans < tmp) ans = tmp;
		sum *= game[i].a;
	}
	ans.Print();
	return 0;
}