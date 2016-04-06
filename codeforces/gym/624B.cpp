#include <cstdio>
const int maxn = 200010;
int t;
char str[maxn], tmp[maxn];
bool solve(int L, int R)
{
	bool flag = 0;
	for(int i = L; i <= R; ++i)
		if(str[i] == 1)
		{
			flag = 1;
			break;
		}
	if(!flag)
		return 0;
	if(~(R - L + 1) & 1)
		return 1;
	int M, cnt = 0;
	for(int i = L + 1; i <= R; i += 2)
		tmp[cnt++] = str[i];
	M = L + cnt - 1;
	for(int i = L + 1; i <= R; i += 2)
		tmp[cnt++] = str[i - 1] ^ str[i + 1];
	R = L + cnt - 1;
	for(int i = 0; i < cnt; ++i)
		str[L + i] = tmp[i];
	return solve(L, M) || solve(M + 1, R);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int i;
		scanf("%s", str);
		for(i = 0; str[i]; ++i)
			str[i] -= '0';
		puts(solve(0, i - 1) ? "LIVES" : "DIES");
	}
	return 0;
}
