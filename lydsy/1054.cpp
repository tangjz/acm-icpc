/*
 * 直接暴搜 难得一见的大水题 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int goal[4][4] = {};
bool Hash[1 << 17] = {};
struct Node
{
	int num[4][4], step;
	bool hash()
	{
		int tot = 0;
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j) tot = tot * 2 + num[i][j];
		if(Hash[tot]) return false;
		return Hash[tot] = true;
	}
	bool cmp()
	{
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j) if(num[i][j] != goal[i][j]) return false;
		return true;
	}
} Q[1 << 17] = {};

int main()
{
	int i, j, l = 0, r = 0;
	char ch[5];
	for(i = 0; i < 4; ++i)
	{
		scanf("%s", ch);
		for(j = 0; j < 4; ++j) Q[0].num[i][j] = ch[j] - '0';
	}
	Q[0].step = 0;
	Q[0].hash();
	for(i = 0; i < 4; ++i)
	{
		scanf("%s", ch);
		for(j = 0; j < 4; ++j) goal[i][j] = ch[j] - '0';
	}
	if(Q[0].cmp()) goto solved;
	while(l <= r)
	{
		for(i = 0; i < 4; ++i)
			for(j = 0; j < 4; ++j)
				if(Q[l].num[i][j])
				{
					if(i > 0 && !Q[l].num[i - 1][j])
					{
						Q[++r] = Q[l];
						swap(Q[r].num[i - 1][j], Q[r].num[i][j]);
						++Q[r].step;
						if(!Q[r].hash()) --r;
						else if(Q[r].cmp()) goto solved;
					}
					if(i < 3 && !Q[l].num[i + 1][j])
					{
						Q[++r] = Q[l];
						swap(Q[r].num[i][j], Q[r].num[i + 1][j]);
						++Q[r].step;
						if(!Q[r].hash()) --r;
						else if(Q[r].cmp()) goto solved;
					}
					if(j > 0 && !Q[l].num[i][j - 1])
					{
						Q[++r] = Q[l];
						swap(Q[r].num[i][j - 1], Q[r].num[i][j]);
						++Q[r].step;
						if(!Q[r].hash()) --r;
						else if(Q[r].cmp()) goto solved;
					}
					if(j < 3 && !Q[l].num[i][j + 1])
					{
						Q[++r] = Q[l];
						swap(Q[r].num[i][j], Q[r].num[i][j + 1]);
						++Q[r].step;
						if(!Q[r].hash()) --r;
						else if(Q[r].cmp()) goto solved;
					}
				}
		++l;
	}
solved:
	printf("%d\n", Q[r].step);
	return 0;
}
