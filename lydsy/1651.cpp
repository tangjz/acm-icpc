#include <cstdio>
const int maxm = 1000002;
int n, seq[maxm], ans;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		int L, R;
		scanf("%d%d", &L, &R);
		++seq[L];
		--seq[R + 1];
	}
	for(int i = 1; i < maxm; ++i)
	{
		seq[i] += seq[i - 1];
		if(ans < seq[i])
			ans = seq[i];
	}
	printf("%d\n", ans);
	return 0;
}
