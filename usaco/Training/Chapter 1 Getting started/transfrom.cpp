/*
ID: tangjin2
LANG: C++
TASK: transform
*/
#include <cstdio>
int n;
char init[11][11], goal[11][11];
bool match()
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) if(init[i][j] != goal[i][j]) return 0;
	return 1;
}
bool transform1()
{
	int i, j;
	char temp[11][11];
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) temp[i][j] = init[i][j];
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) init[i][j] = temp[n - j - 1][i];
	return match();
}
bool transform2()
{
	int i, j;
	char temp[11][11];
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) temp[i][j] = init[i][j];
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) init[i][j] = temp[i][n - j - 1];
	return match();
}
int test()
{
	if(transform1()) return 1;
	if(transform1()) return 2;
	if(transform1()) return 3;
	transform1();
	if(transform2()) return 4;
	if(transform1() || transform1() || transform1())return 5;
	if(transform1())return 6;
	return 7;
}
int main()
{
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; ++i) scanf("%s", init[i]);
	for(i = 0; i < n; ++i) scanf("%s", goal[i]);
	printf("%d\n", test());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
