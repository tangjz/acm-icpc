#include <ctime>
#include <cstdio>
#include <cstdlib>
typedef long long LL;
const int sp[] = {1,4,8,25,49,148,288,865,1681,5044,9800,29401,57121,171364,332928,998785,1940449,5821348,11309768,33929305,65918161,197754484,384199200};
int main()
{
	FILE *fin = fopen("1144.in", "w");
	int t = 11000 - rand() % 1000, c = 0;
	for(int i = 0; i < 23; ++i, ++c)
		fprintf(fin, "%d\n", sp[i]);
	for(int i = 0; c < t; ++i, ++c)
	{
		LL n;
		if((rand() & 3) <= 1)
		{
			n = rand() % 44720 + 1;
			n = n * (n + 1) >> 1;
			if(rand() & 1)
				++n;
			if(n > 1000000000L)
				return -1;
		}
		else
		{
			n = (((LL)rand() << 15) | rand()) % 1000000000L + 1;
		}
		fprintf(fin, "%d\n", n);
	}
	fclose(fin);
	system("1144.exe < 1144.in > 1144.out");
	return 0;
}
