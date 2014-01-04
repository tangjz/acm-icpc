/*
ID: tangjin2
LANG: C++
TASK: frac1
*/
#include <fstream>
#include <iostream>
using namespace std;
int n;
void dfs(int x1,int y1,int x2,int y2)
{
   if(y1 + y2 > n) return;
   dfs(x1, y1, x1 + x2, y1 + y2);
   printf("%d/%d\n", x1 + x2, y1 + y2);
   dfs(x1 + x2, y1 + y2, x2, y2);
}
int main()
{
   freopen("frac1.in", "r", stdin);
   freopen("frac1.out", "w", stdout);
   scanf("%d", &n);
   printf("0/1\n");
   dfs(0, 1, 1, 1);
   printf("1/1\n");
   fclose(stdin);
   fclose(stdout);
   return 0;
}
