#include <cstdio>
const int maxn = 1010;
int n, stack[maxn], top, nxt, seq[maxn];
int main()
{
	while(scanf("%d", &n) != EOF && n)
	{
		while(scanf("%d", &seq[0]) != EOF && seq[0])
		{
			for(int i = 1; i < n; ++i)
				scanf("%d", &seq[i]);
			nxt = 1;
			top = -1;
			for(int i = 0; i < n; ++i)
			{
				while(top < 0 || nxt <= n && stack[top] != seq[i])
					stack[++top] = nxt++;
				if(stack[top] == seq[i])
					--top;
				else
					break;
			}
			puts(top >= 0 ? "No" : "Yes");
		}
		puts("");
	}
	return 0;
}
