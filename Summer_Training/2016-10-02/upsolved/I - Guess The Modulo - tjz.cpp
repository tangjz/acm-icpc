#include <ctime>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 101, maxv = 1000000000, maxs = 32000;
int n, a[maxn], idx, low = 1, mx;
long long sum;
void insert(int x)
{
	sum -= a[idx];
	a[idx] = x;
	sum += a[idx++];
	if(idx == n)
		idx = 0;
}
int main()
{
	// typedef long long LL;
	// unsigned seed = time(0);
	// printf("seed : %d\n", seed);
	// srand(seed);
	// int M = ((LL)rand() << 15 | rand()) % (maxv - 2 + 1) + 2;
	// printf("modulo : %d\n", M);
	int x, y;
	// n = rand() % (100 - 2 + 1) + 1; printf("n : %d\n", n);
	scanf("%d", &n);
	// printf("seq :");
	for(int i = 0; i < n - 1; ++i)
	{
		//x = ((LL)rand() << 15 | rand()) % (maxv + 1); printf(" %d", x);
		scanf("%d", &x);
		insert(x);
	}
	// putchar('\n');
	{ // first
		int y1, y2;
		insert(0);
		printf("? %d\n", 0);
		fflush(stdout);
		//y1 = sum % M; printf("ret : %d\n", y1);
		scanf("%d", &y1);
		int tmp = (y1 << 1) - a[idx];
		insert(y1);
		low = max(low, y1);
		tmp -= a[idx];
		if(tmp < 0)
			x = min(-tmp - 1, maxv);
		else
			x = max(maxv - tmp, 0);
		tmp += x;
		insert(x);
		printf("? %d\n", x);
		fflush(stdout);
		//y2 = sum % M; printf("ret : %d\n", y2);
		scanf("%d", &y2);
		insert(y2);
		low = max(low, y2);
		if(tmp < 0)
			mx = y2 - tmp;
		else
			mx = tmp - y2;
		y = y2;
	}
	if(mx > maxv) // first divide
	{
		int lim = (int)ceil(sqrt(mx));
		static int tot = 0, prime[maxs];
		static bool vis[maxs] = {};
		for(int i = 2; i <= lim; ++i)
		{
			if(!vis[i])
				prime[tot++] = i;
			for(int j = 0; j < tot && i * prime[j] <= lim; ++j)
			{
				vis[i * prime[j]] = 1;
				if(i % prime[j] == 0)
					break;
			}
		}
		int tmp = mx;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
			{
				int temp = mx / prime[i];
				if(temp > low)
				{
					int x = temp - (sum - a[idx]) % temp;
					insert(x);
					printf("? %d\n", x);
					fflush(stdout);
					//y = sum % M; printf("ret : %d\n", y);
					scanf("%d", &y);
					if(!y)
						mx /= prime[i];
					else
						low = max(low, y);
					insert(y);
				}
				for(tmp /= prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
			}
		if(tmp > 1)
		{
			int temp = mx / tmp;
			if(temp > low)
			{
				int x = temp - (sum - a[idx]) % temp;
				insert(x);
				printf("? %d\n", x);
				fflush(stdout);
				//y = sum % M; printf("ret : %d\n", y);
				scanf("%d", &y);
				if(!y)
					mx /= tmp;
				else
					low = max(low, y);
				insert(y);
			}
		}
	}
	while(low + 1 < mx) // still divide
	{
		int temp = mx, x = temp - 1 - (sum - a[idx]) % temp;
		insert(x);
		printf("? %d\n", x);
		fflush(stdout);
		//y = sum % M; printf("ret : %d\n", y);
		scanf("%d", &y);
		if(y < temp - 1)
			mx = __gcd(mx, (int)abs(temp - 1 - y));
		low = max(low, y);
		insert(y);
	}
	printf("! %d\n", mx);
	//puts(mx == M ? "YES" : "NO");
	return 0;
}
