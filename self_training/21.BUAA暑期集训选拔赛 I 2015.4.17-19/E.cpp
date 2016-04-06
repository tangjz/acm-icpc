#include <cstdio>
/*
    07
  18  08
17  06  09
  05  01
16  00  10
  04  02
15  03  11
  14  12
    13
*/
const int adj[7][7] = {
{ 3,  2,  4,  0,  1,  5,  6},
{ 2, 10,  0,  1,  9,  6,  8},
{12, 11,  3,  2, 10,  0,  1},
{13, 12, 14,  3,  2,  4,  0},
{14,  3, 15,  4,  0, 16,  5},
{ 4,  0, 16,  5,  6, 17, 18},
{ 0,  1,  5,  6,  8, 18,  7}};
char s[129];
int v[19], t[7];
bool equal(int mask)
{
	for(int i = 0; i < 19; ++i)
		v[i] = (mask >> i) & 1;
	for(int i = 0; i < 7; ++i)
	{
		int tmp = 0;
		for(int j = 6; j >= 0; --j)
			tmp = (tmp << 1) | v[adj[i][j]];
		t[i] = s[tmp];
	}
	int tt = 0;
	for(int i = 6; i >= 0; --i)
		tt = (tt << 1) | t[adj[0][i]];
	tt = s[tt];
	return t[0] == tt;
}
int main()
{
	while(scanf("%s", s) == 1 && s[0] != '#')
	{
		for(int i = 0; i < 128; ++i)
			s[i] -= '0';
		bool flag = 0;
		for(int i = 0; i < 1 << 19; ++i)
			if(!equal(i))
			{
				flag = 1;
				break;
			}
		puts(!flag ? "yes" : "no");
	}
	return 0;
}
