/*
 * 暴搜即可... 注意输出要倒着... 
 */
#include <cstdio>
#include <string>
using namespace std;
const string a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int n, b, c[20] = {}, t[20] = {};
void print() { for(int i = n; i; --i) printf("%c", a[c[i]]); printf("\n"); }
void find(int dep)
{
	if(dep == n) for(int i = 1; i < b; ++i) { c[n] += t[n]; print(); }
	else
		for(int i = 1; i < b; ++i)
		{
			find(dep + 1);
			c[dep] += t[dep]; print();
			if(!c[dep] || c[dep] == b - 1) find(dep + 1);
		}
	t[dep] *= -1;
}

int main()
{
	scanf("%d%d", &n, &b);
	for(int i = 1; i <= n; ++i) { c[i] = 0; t[i] = 1; printf("0"); }
	printf("\n");
	find(1);
	return 0;
}
