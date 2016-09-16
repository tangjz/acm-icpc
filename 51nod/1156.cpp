// arxiv.org/pdf/1004.1278.pdf
// ON THE PALINDROMIC DECOMPOSITION OF BINARY WORDS
// 8th April, 2010
#include <stdio.h>
const int maxn = 10001, maxm = 12;
const char *head = "aabab", *cycle = "bbaaba", *tail = "bbaaababb";
int n, f[maxm];
char str[maxn], tmp[maxm + 1];
int main()
{
	scanf("%d", &n);
	if(n < maxm)
	{
		int mx = 0, id = -1;
		for(int s = 0; s < 1 << n; ++s)
		{
			for(int i = 0; i < n; ++i)
				tmp[i + 1] = 'a' + ((s >> i) & 1);
			f[0] = 0;
			for(int i = 1; i <= n; ++i)
			{
				f[i] = maxm;
				for(int j = 0; j < i; ++j)
				{
					int k;
					for(k = 0; j + 1 + k < i - k && tmp[j + 1 + k] == tmp[i - k]; ++k);
					if(j + 1 + k >= i - k && f[i] > f[j] + 1)
						f[i] = f[j] + 1;
				}
			}
			if(mx < f[n])
			{
				mx = f[n];
				id = s;
			}
		}
		for(int i = 0; i < n; ++i)
			str[i] = 'a' + ((id >> i) & 1);
	}
	else if(n % 6 == 2)
	{
		for(int i = 0; i < 5; ++i)
			str[i] = head[i];
		for(int i = 5, j = 0; i + 9 < n; ++i, (j < 5 ? ++j : j = 0))
			str[i] = cycle[j];
		for(int i = 0; i < 9; ++i)
			str[n - 9 + i] = tail[i];
	}
	else
	{
		for(int i = 0; i < 5; ++i)
			str[i] = head[i];
		for(int i = 5, j = 0; i < n; ++i, (j < 5 ? ++j : j = 0))
			str[i] = cycle[j];
	}
	str[n] = '\0';
	puts(str);
	return 0;
}
