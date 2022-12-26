#include <map>
#include <queue>
#include <cstdio>
using namespace std;
map<int, int> Hash;
struct Node
{
	int num[3][3], x, y, step;
	bool hash()
	{
		int cnt = 0;
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j) cnt = cnt * 10 + num[i][j];
		if(Hash[cnt]) return false;
		return (Hash[cnt] = 1);
	}
	bool check()
	{
		if(num[0][0] == 1 && num[0][1] == 2 && num[0][2] == 3
		&& num[1][0] == 8 && num[1][1] == 0 && num[1][2] == 4
		&& num[2][0] == 7 && num[2][1] == 6 && num[2][2] == 5) return true;
		return false;
	}
} tmp, now;
queue<Node> Q;
int main()
{
	char ch[10];
	scanf("%s", ch);
	for(int i = 0; i < 9; ++i)
	{
		now.num[i / 3][i % 3] = ch[i] - '0';
		if(ch[i] == '0') { now.x = i / 3; now.y = i % 3; }
	}
	if(now.check()) goto solved;
	now.hash();
	Q.push(now);
	while(!Q.empty())
	{
		tmp = Q.front(); Q.pop();
		int x = tmp.x, y = tmp.y;
		if(x - 1 >= 0)
		{
			now = tmp;
			now.num[x][y] = now.num[x - 1][y]; now.num[x - 1][y] = 0;
			if(now.hash())
			{
				++now.step;
				if(now.check()) goto solved;
				--now.x;
				Q.push(now);
			}
		}
		if(y - 1 >= 0)
		{
			now = tmp;
			now.num[x][y] = now.num[x][y - 1]; now.num[x][y - 1] = 0;
			if(now.hash())
			{
				++now.step;
				if(now.check()) goto solved;
				--now.y;
				Q.push(now);
			}
		}
		if(x + 1 < 3)
		{
			now = tmp;
			now.num[x][y] = now.num[x + 1][y]; now.num[x + 1][y] = 0;
			if(now.hash())
			{
				++now.step;
				if(now.check()) goto solved;
				++now.x;
				Q.push(now);
			}
		}
		if(y + 1 < 3)
		{
			now = tmp;
			now.num[x][y] = now.num[x][y + 1]; now.num[x][y + 1] = 0;
			if(now.hash())
			{
				++now.step;
				if(now.check()) goto solved;
				++now.y;
				Q.push(now);
			}
		}
	}
solved:
	printf("%d\n", now.step);
	return 0;
}
