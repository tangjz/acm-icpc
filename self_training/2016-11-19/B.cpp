#include <stdio.h>
#include <cstring>
const int maxn = 15;
int len;
char str[maxn], out[maxn];
int main()
{
	scanf("%s", str);
	len = strlen(str);
	for(int i = 0; i <= len; ++i)
	{
		int tot = 0;
		for(int j = 0; j < i; ++j)
			out[tot++] = str[j];
		out[tot++] = -1;
		for(int j = i; j < len; ++j)
			out[tot++] = str[j];
		out[tot] = '\0';
		bool flag = 1;
		for(int j = 0, k = tot - 1; j < k; ++j, --k)
		{
			if(out[j] == -1 || out[k] == -1 || out[j] == out[k])
				continue;
			flag = 0;
			break;
		}
		if(flag)
		{
			for(int j = 0; j < tot; ++j)
				if(out[j] == -1)
				{
					int k = tot - 1 - j;
					if(j == k)
						out[j] = 'a';
					else
						out[j] = out[k];
					break;
				}
			puts(out);
			return 0;
		}
	}
	puts("NA");
	return 0;
}
