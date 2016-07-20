#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;

const int NMAX = 300, MOD = 1000000007;

int N, T, reduce;
int status[4][4], Next[4][4];
int mask[4][4] = {{}, {0, 1, 1<<1, 1<<2}, {0, 1<<3, 0, 1<<4}, {0, 1<<5, 1<<6, 1<<7}};
int maskNumber[4][4] = {{}, {0, 0, 1, 2}, {0, 3, 0, 4}, {0, 5, 6, 7}};
int trans[NMAX][NMAX], trans2[NMAX][NMAX], A[NMAX][NMAX], B[NMAX][NMAX], res[NMAX][NMAX] = {};
int init[4][4], arrive[NMAX][NMAX], number[NMAX];

void DFS(int x, int i, int j)
{
	int l, m, s = 0;
	if(i == 3 && j == 4)
	{
		//~ for(l = 1;l <= 3;l += 1)
		//~ {
			//~ for(m = 1;m <= 3;m += 1)
				//~ printf("%d ", init[l][m]);
			//~ printf("\n");
		//~ }
		//printf("---->\n");
		for(l = 1;l <= 3;l += 1)
		{
			for(m = 1;m <= 3;m += 1)
			{
				//printf("%d ", Next[l][m]);
				if(l == 2 && m == 2)
					continue;
				//printf("(%d %d)\n", Next[l][m], maskNumber[l][m]);
				s |= Next[l][m]<<maskNumber[l][m];
			}
			//printf("\n");
		}
		trans[s][x] += 1;
		/*if(s == 255)
		{
			printf("%d %d %d\n", x, s, A[s][x]);
			getchar();
			getchar();
		}
		*/
		//printf("-----------------\n");
		return;
	}
	if(j == 4)
	{
		i += 1;
		j = 1;
	}
	if(status[i][j])
		DFS(x, i, j + 1);
	else
	{
		status[i][j] = 1;
		Next[i][j] = 1;
		DFS(x, i, j + 1);
		Next[i][j] = 0;
		if(j < 3 && !status[i][j + 1])
		{
			status[i][j + 1] = 1;
			DFS(x, i, j + 1);
			status[i][j + 1] = 0;
		}
		if(i < 3 && !status[i + 1][j])
		{
			status[i + 1][j] = 1;
			DFS(x, i, j + 1);
			status[i + 1][j] = 0;
		}
		status[i][j] = 0;
	}
}

void times(int Z[NMAX][NMAX], int X[NMAX][NMAX], int Y[NMAX][NMAX])
{
	int i, j, k;
	memset(res, 0, sizeof(res));
	for(i = 0;i < reduce;i += 1)
	{
		for(j = 0;j < reduce;j += 1)
		{
			for(k = 0;k < reduce;k += 1)
				res[i][k] = (res[i][k] + (long long)X[i][j] * Y[j][k]) % MOD;
		}
	}
	//printf("(%d)\n", res[255][0]);
	memcpy(Z, res, 4 * NMAX * NMAX);
}

void quickPower(int x)
{
	int i;
	memcpy(A, trans2, sizeof(A));
	memset(B, 0, sizeof(B));
	for(i = 0;i < reduce;i += 1)
		B[i][i] = 1;
	while(x)
	{
		if(x & 1)
		{
			times(B, A, B);
			//printf("%d!\n", B[255][0]);
		}
		times(A, A, A);
		x >>= 1;
	}
}

void floyd()
{
	int i, j, k;
	for(i = 0;i < 256;i += 1)
	{
		arrive[i][i] = 1;
		for(j = 0;j < 256;j += 1)
			arrive[i][j] = (bool)trans[j][i];
	}
	for(k = 0;k < 256;k += 1)
	{
		for(i = 0;i < 256;i += 1)
		{
			for(j = 0;j < 256;j += 1)
				arrive[i][j] = arrive[i][j] || (arrive[i][k] && arrive[k][j]);
		}
	}
	memset(number, ~0u, sizeof(number));
	for(i = k = 0;i < 256;i += 1)
	{
		if(arrive[0][i])
			number[i] = k++;
	}
	reduce = k + 10;
	//printf("%d\n", reduce);
	for(i = 0;i <= 255;i += 1)
	{
		for(j = 0;j <= 255;j += 1)
		{
			if(number[i] >= 0 && number[j] >= 0)
				trans2[number[i]][number[j]] = trans[i][j];
		}
	}
}

int main()
{
	int i, j, k;
	for(i = 0;i < 256;i += 1)
	{
		for(j = 1;j <= 3;j += 1)
		{
			for(k = 1;k <= 3;k += 1)
				status[j][k] = (bool)(mask[j][k] & i);
		}
		status[2][2] = 1;
		memcpy(init, status, 4 * 4 * 4);
		DFS(i, 1, 1);
	}
	//printf("%d\n", A[0][0]);
	floyd();
	scanf("%d", &T);
	for(i = 1;i <= T;i += 1)
	{
		scanf("%d", &N);
		quickPower(N);
		printf("Case %d: %d\n", i, B[0][0]);
	}
	exit(0);
}
