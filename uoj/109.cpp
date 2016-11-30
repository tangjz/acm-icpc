#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int maxV = 300, maxw = 1000000, maxE = 5000, maxQ = 10, INF = 1000000000;
const int minV2 = 71, maxV2 = 999, minE2 = 1501, maxE2 = 999999;
int typ, tlimit, tcnt;
int V, E, Q, size[maxV], e[maxV][maxV][2], s[maxQ], t[maxQ];
int V2, E2, e2[maxE2][2];
int Hash[(maxV2 + 1) * (maxV2 + 1)];

int main()
{
	srand(time(NULL));
	scanf("%d %d", &typ, &tlimit);
	tcnt = 0;
	switch(typ)
	{
		case 1:
			V = 101;
			Q = 1;
			break;
		case 2:
			V = 100;
			E = 0;
			for(int i = 1; i < V; ++i)
			{
				e[i][size[i]][0] = i - 1;
				e[i][size[i]][1] = 1;
				++size[i];
				++E;
			}
			for(int i = V - 1; i >= 0; --i)
			{
				for(int j = 0; j < i - 1; ++j)
				{
					e[i][size[i]][0] = j;
					e[i][size[i]][1] = rand() % (maxw - (i - j + 1)) + (i - j + 1);
					++size[i];
					++E;
					if(E == 1050)
						break;
				}
				if(E == 1050)
					break;
			}
			Q = 10;
			for(int i = 0; i < Q; ++i)
				s[i] = V - 1;
			break;
		case 3:
			V = 101;
			Q = 1;
			break;
		case 4:
			V = 33;
			for(int i = 0; i < V - 1; ++i)
				if(i & 1)
				{
					e[i][size[i]][0] = i + 1;
					e[i][size[i]][1] = 1 - (1 << 17 - (i >> 1));
					++size[i];
				}
				else
				{
					e[i][size[i]][0] = i + 1;
					e[i][size[i]][1] = (1 << 17 - (i >> 1)) - 1;
					++size[i];
					e[i][size[i]][0] = i + 2;
					e[i][size[i]][1] = (1 << 16 - (i >> 1)) - 1;
					++size[i];
				}
			Q = 6;
			for(int i = 0; i < Q; ++i)
				t[i] = V - 1;
			break;
		case 5:
			V = 300;
			E = 0;
			for(int i = 1; i < V; ++i)
			{
				e[i][size[i]][0] = i - 1;
				e[i][size[i]][1] = 1;
				++size[i];
				++E;
			}
			for(int i = V - 1; i >= 0; --i)
			{
				for(int j = 0; j < i - 1; ++j)
				{
					e[i][size[i]][0] = j;
					e[i][size[i]][1] = rand() % (maxw - (i - j + 1)) + (i - j + 1);
					++size[i];
					++E;
					if(E == 347)
						break;
				}
				if(E == 347)
					break;
			}
			Q = 10;
			for(int i = 0; i < Q; ++i)
				s[i] = V - 1;
			break;
		case 6:
			V = 33;
			for(int i = 0; i < V - 1; ++i)
				if(i & 1)
				{
					e[i][size[i]][0] = i + 1;
					e[i][size[i]][1] = 1 - (1 << 17 - (i >> 1));
					++size[i];
				}
				else
				{
					e[i][size[i]][0] = i + 1;
					e[i][size[i]][1] = (1 << 17 - (i >> 1)) - 1;
					++size[i];
					e[i][size[i]][0] = i + 2;
					e[i][size[i]][1] = (1 << 16 - (i >> 1)) - 1;
					++size[i];
				}
			Q = 6;
			for(int i = 0; i < Q; ++i)
				t[i] = V - 1;
			break;
		case 7:
			V2 = 71;
			tcnt = 2;
			for(int i = 0; i < V2; ++i)
			{
				for(int j = i + 1; j < V2; ++j)
				{
					tcnt += 2;
					if(tcnt > tlimit)
						break;
					e2[E2][0] = i;
					e2[E2][1] = j;
					++E2;
				}
				if(tcnt > tlimit)
					break;
			}
			break;
		case 8:
			V2 = 78;
			tcnt = 2;
			for(int i = 0; i < V2; i += 2)
			{
				for(int j = 1; j < V2; j += 2)
				{
					tcnt += 2;
					if(tcnt > tlimit)
						break;
					e2[E2][0] = i;
					e2[E2][1] = j;
					++E2;
				}
				if(tcnt > tlimit)
					break;
			}
			break;
	}
	if(typ <= 6)
	{
		printf("%d\n", V);
		for(int i = 0; i < V; ++i)
		{
			printf("%d", size[i]);
			for(int j = 0; j < size[i]; ++j)
				printf(" %d %d", e[i][j][0], e[i][j][1]);
			putchar('\n');
		}
		printf("%d\n", Q);
		for(int i = 0; i < Q; ++i)
			printf("%d %d\n", s[i], t[i]);
	}
	else
	{
		printf("%d %d\n", V2, E2);
		for(int i = 0; i < E2; ++i)
			printf("%d %d\n", e2[i][0], e2[i][1]);
	}
	return 0;
}
