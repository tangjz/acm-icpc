#include <cstdio>
const int maxn = 1000010;
int q, top1, stack1[maxn], top2, stack2[maxn], s[maxn], f[maxn];
int max(int x, int y)
{
	return x < y ? y : x;
}
int main()
{
	f[0] = -2333;
	while(scanf("%d", &q) == 1)
	{
		top1 = top2 = 0;
		while(q--)
		{
			int x;
			char op[2];
			scanf("%s", op);
			if(op[0] == 'I')
			{
				scanf("%d", &x);
				stack1[++top1] = x;
				s[top1] = s[top1 - 1] + stack1[top1];
				f[top1] = max(f[top1 - 1], s[top1]);
			}
			else if(op[0] == 'D')
			{
				if(!top1)
					continue;
				--top1;
			}
			else if(op[0] == 'L')
			{
				if(!top1)
					continue;
				stack2[++top2] = stack1[top1--];
			}
			else if(op[0] == 'R')
			{
				if(!top2)
					continue;
				stack1[++top1] = stack2[top2--];
				s[top1] = s[top1 - 1] + stack1[top1];
				f[top1] = max(f[top1 - 1], s[top1]);
			}
			else
			{
				scanf("%d", &x);
				printf("%d\n", f[x]);
			}
		}
	}
	return 0;
}
