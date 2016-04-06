//#include <ctime>
//#include <iostream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int n, vis[3][11], vis2;

int main()
{
	scanf("%d", &n);
	if(n <= 2)
	{
		for(int i = 0; i < n; ++i)
			vis[i][0] = 1;
	}
	else
	{
		vis2 = 1;
		--n;
		for(int i = 0; i < n; ++i)
			vis[i % 3][i / 3] = 1;
	}
	printf("+------------------------+\n|");
	for(int i = 0; i < 11; ++i)
		printf("%s", vis[0][i] ? "O." : "#.");
	printf("|D|)\n|");
	for(int i = 0; i < 11; ++i)
		printf("%s", vis[1][i] ? "O." : "#.");
	printf("|.|\n|");
	printf("%s", vis2 ? "O." : "#.");
	printf("......................|\n|");
	for(int i = 0; i < 11; ++i)
		printf("%s", vis[2][i] ? "O." : "#.");
	printf("|.|)\n+------------------------+\n");
	return 0;
}
