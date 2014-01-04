/*
ID: tangjin2
LANG: C++
TASK: gift1
*/
#include <cstdio>
#include <cstring>
char name[10][15], NG[15];
int money[10], NP;
int main()
{
	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);
	int i, j, temp, count, div;
	scanf("%d", &NP);
	for(i = 0; i < NP; ++i) scanf("%s", name[i]);
	for(i = 0; i < NP; ++i)
	{
		memset(NG, 0, sizeof NG);
		scanf("%s%d%d", NG, &count, &div);
		if(!div) continue;
		for(temp = 0; temp < NP; ++temp) if(!strcmp(NG, name[temp])) break;
		count /= div;
		money[temp] -= count * div;
		for(j = 0; j < div; ++j)
		{
			memset(NG, 0, sizeof NG);
			scanf("%s", NG);
			for(temp = 0; temp < NP; ++temp) if(!strcmp(NG, name[temp])) break;
			money[temp] += count;
		}
	}
	for(i = 0; i < NP; ++i) printf("%s %d\n", name[i], money[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
