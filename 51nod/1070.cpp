#include <set>
#include <stdio.h>
const int maxn = 46;
int t, n, fib[maxn];
std::set<int> Hash;
int main()
{
	fib[1] = 1;
	for(int i = 2; i < maxn; ++i)
		Hash.insert(fib[i] = fib[i - 1] + fib[i - 2]);
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		puts(!Hash.count(n) ? "A" : "B");
	}
	return 0;
}
