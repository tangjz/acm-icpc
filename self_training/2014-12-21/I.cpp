#include <cstdio>
#include <cstring>
const char *out = "mspc";
int n, now[20], seq[150], all[40], wan[40], fin, push[150];
char str[150];
int trans(char *s)
{
	for(int i = 0; i < 4; ++i)
		if(s[1] == out[i])
			return i * 9 + s[0] - '1';
	return -1;
}
bool matchless()
{
	bool flag = 0;
	for(int i = 0; i < 3; ++i)
	{
		if(!all[i * 9] || !all[i * 9 + 8])
			return 0;
		--all[i * 9], --all[i * 9 + 8];
		++wan[i * 9], ++wan[i * 9 + 8];
		if(!flag && all[i * 9])
		{
			--all[i * 9];
			++wan[i * 9];
			flag = 1;
		}
		if(!flag && all[i * 9 + 8])
		{
			--all[i * 9 + 8];
			++wan[i * 9 + 8];
			flag = 1;
		}
	}
	for(int i = 0; i < 7; ++i)
	{
		if(!all[27 + i])
			return 0;
		--all[27 + i];
		++wan[27 + i];
		if(!flag && all[27 + i])
		{
			--all[27 + i];
			++wan[27 + i];
			flag = 1;
		}
	}
	if(flag)
		return 1;
	return 0;
}
bool sevenpair()
{
	int cnt = 0;
	for(int i = 0; i < 34 && cnt < 7; ++i)
		if(all[i] >= 2)
		{
			all[i] -= 2;
			wan[i] += 2;
			++cnt;
		}
	if(cnt == 7)
		return 1;
}
bool check(int dep)
{
	if(dep == 4)
	{
		for(int i = 0; i < 34; ++i)
			if(all[i] >= 2)
			{
				all[i] -= 2;
				wan[i] += 2;
				return 1;
			}
		return 0;
	}
	for(int i = 0; i < 34; ++i)
		if(all[i] >= 3)
		{
			all[i] -= 3;
			wan[i] += 3;
			if(check(dep + 1))
				return 1;
			all[i] += 3;
			wan[i] -= 3;
		}
	for(int t = 0; t < 3; ++t)
		for(int j = 0; j < 7; ++j)
		{
			int i = t * 9 + j;
			if(all[i] && all[i + 1] && all[i + 2])
			{
				--all[i], --all[i + 1], --all[i + 2];
				++wan[i], ++wan[i + 1], ++wan[i + 2];
				if(check(dep + 1))
					return 1;
				++all[i], ++all[i + 1], ++all[i + 2];
				--wan[i], --wan[i + 1], --wan[i + 2];
			}
		}
	return 0;
}
void rebuild()
{
	for(int i = 0; i < 34; ++i)
	{
		all[i] += wan[i];
		wan[i] = 0;
	}
}
bool judge(int lim)
{
	memset(all, 0, sizeof all);
	memset(wan, 0, sizeof wan);
	for(int i = 0; i < 13; ++i)
		++all[now[i]];
	for(int i = 0; i < lim; ++i)
		++all[seq[i]];
	if(!matchless())
	{
		rebuild();
		if(!sevenpair())
		{
			rebuild();
			if(!check(0))
				return 0;
		}
	}
	return 1;
}
int main()
{
	while(scanf("%s", str) != EOF)
	{
		now[0] = trans(str);
		++all[now[0]];
		for(int i = 1; i < 13; ++i)
		{
			scanf("%s", str);
			now[i] = trans(str);
			++all[now[i]];
		}
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str);
			seq[i] = trans(str);
			++all[seq[i]];
		}
		int L = 0, R = n, M;
		while(L < R)
		{
			M = L + R >> 1;
			if(judge(M))
				R = M;
			else
				L = M + 1;
		}
		judge(L);
		fin = push[0] = 0;
		for(int i = 0; i < 13; ++i)
			if(wan[now[i]])
			{
				--wan[now[i]];
				++fin;
			}
			else
				push[++push[0]] = now[i];
		for(int i = 0; i < n; ++i)
		{
			if(wan[seq[i]])
			{
				--wan[seq[i]];
				++fin;
			}
			else
				push[++push[0]] = seq[i];
			if(fin == 14)
			{
				puts("Ron");
				break;
			}
			printf("%d%c\n", push[push[0]] % 9 + 1, out[push[push[0]] / 9]);
			--push[0];
		}
	}
	return 0;
}
