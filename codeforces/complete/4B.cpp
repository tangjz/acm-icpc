#include <cstdio>
int d, sum, min[40], max[40];
int main()
{
	scanf("%d%d", &d, &sum);
	for(int i = 1; i <= d; ++i)
	{
		scanf("%d%d", min + i, max + i);
		min[0] += min[i];
		max[0] += max[i];
	}
	if(sum < min[0] || max[0] < sum) puts("NO");
	else
	{
		for(int i = 1; i <= d; ++i)
		{
			if(min[0] + max[i] - min[i] >= sum)
			{
				min[i] += sum - min[0];
				break;
			}
			min[0] += max[i] - min[i];
			min[i] = max[i];
		}
		puts("YES");
		for(int i = 1; i <= d; ++i) printf("%d ", min[i]);
	}
	return 0;
}
