#include <cstdio>
#include <cstring>
const int maxn = 101, maxm = 701;
int t, m;
char str[maxn], seq[maxm], mx, out[maxm];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		m = 0;
		scanf("%s", str);
		seq[m++] = mx = str[0];
		for(int i = 1; str[i]; ++i)
		{
			if(seq[m - 1] == str[i])
				seq[m++] = str[i];
			for( ; seq[m - 1] < str[i]; seq[m] = seq[m - 1] + 1, ++m);
			for( ; seq[m - 1] > str[i]; seq[m] = seq[m - 1] - 1, ++m);
			if(mx < str[i])
				mx = str[i];
		}
		for( ; mx > '0'; --mx)
		{
			for(int i = 0; i < m; ++i)
				out[i] = seq[i] < mx ? '*' : '+';
			out[m] = '\0';
			puts(out);
		}
	}
	return 0;
}
