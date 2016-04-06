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
int n, m;
char str[2][30];
int main()
{
	scanf("%d%d%s%s", &n, &m, str[0], str[1]);
	puts(str[0][0] == str[0][n - 1] || str[1][0] == str[1][m - 1] || (str[0][0] == '<' && str[1][0] == '^') || (str[0][0] == '>' && str[1][0] == 'v') ? "NO" : "YES");
	return 0;
}
