#include <cstdio>
const int d[10][4] = {
{0, 0, 0, 0},
{0, 0, 0, 0},
{1, 0, 0, 0},
{0, 1, 0, 0},
{2, 0, 0, 0},
{0, 0, 1, 0},
{1, 1, 0, 0},
{0, 0, 0, 1},
{3, 0, 0, 0},
{0, 2, 0, 0}
};
long long L, R, X, a[4], f[19][55][37][19][19];
bool flag;
void fact()
{
	int s[4] = {2, 3, 5, 7};
	for(int i = 0; i < 4; ++i)
	{
		a[i] = 0;
		while(X % s[i] == 0)
		{
			++a[i];
			X /= s[i];
		}
	}
	flag = X > 1 || a[0] > 54 || a[1] > 36 || a[2] > 18 || a[3] > 18;
} 
long long sum(long long M)
{
	if(M <= 0 || flag)
		return 0;
	int len = 0, num[20] = {};
	long long sum = 0;
	while(M > 0)
	{
		num[len++] = M % 10;
		M /= 10;
	}
	long long now[4] = {a[0], a[1], a[2], a[3]};
	for(int i = len - 1; i > 0; --i)
		sum += f[i][now[0]][now[1]][now[2]][now[3]];
	for(int i = len - 1; i >= 1; --i)
	{
		if(!num[i])
			return sum;
		for(int j = 1; j < num[i]; ++j)
		{
			now[0] -= d[j][0];
			now[1] -= d[j][1];
			now[2] -= d[j][2];
			now[3] -= d[j][3];
			if(now[0] >= 0 && now[1] >= 0 && now[2] >= 0 && now[3] >= 0)
				sum += f[i][now[0]][now[1]][now[2]][now[3]];
			now[0] += d[j][0];
			now[1] += d[j][1];
			now[2] += d[j][2];
			now[3] += d[j][3];
		}
		now[0] -= d[num[i]][0];
		now[1] -= d[num[i]][1];
		now[2] -= d[num[i]][2];
		now[3] -= d[num[i]][3];
		if(now[0] < 0 || now[1] < 0 || now[2] < 0 || now[3] < 0)
			return sum;
	}
	long long tmp = 1;
	for(int i = 0; i < now[0] && tmp < 10; ++i)
		tmp *= 2;
	for(int i = 0; i < now[1] && tmp < 10; ++i)
		tmp *= 3;
	for(int i = 0; i < now[2] && tmp < 10; ++i)
		tmp *= 5;
	for(int i = 0; i < now[3] && tmp < 10; ++i)
		tmp *= 7;
	if(tmp <= num[0])
		++sum;
	return sum;
}
int main()
{
	f[0][0][0][0][0] = 1;
	for(int len = 1; len <= 18; ++len)
		for(int i = 0; i <= (len << 1) + len; ++i)
			for(int j = 0; j <= len << 1; ++j)
				for(int k = 0; k <= len; ++k)
					for(int l = 0; l <= len; ++l)
					{
						for(int o = 1; o <= 9; ++o)
							if(i >= d[o][0] && j >= d[o][1] && k >= d[o][2] && l >= d[o][3])
								f[len][i][j][k][l] += f[len - 1][i - d[o][0]][j - d[o][1]][k - d[o][2]][l - d[o][3]];
					}
	while(scanf("%lld%lld%lld", &L, &R, &X) == 3)
	{
		fact();
		printf("%lld\n", sum(R) - sum(L - 1));
	}
	return 0; 
}

