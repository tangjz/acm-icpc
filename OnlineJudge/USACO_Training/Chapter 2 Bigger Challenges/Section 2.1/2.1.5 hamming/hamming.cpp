/*
ID: tangjin2
LANG: C++
TASK: hamming
*/
#include <fstream>
#include <iostream>
using namespace std;
int n, b, d, maxx, ans[64] = {};
bool check(int x, int y)
{
   int cnt = 0;
   while(x || y)
   {
      if((x & 1) != (y & 1)) ++cnt;
      x >>= 1;
      y >>= 1;
   }
   if(cnt >= d) return true;
   return false;
}
bool compare(int x, int dep)
{
   while(dep)
   {
      if(!check(x, ans[dep - 1])) return false;
      --dep;
   }
   return true;
}
void dfs(int dep, int from)
{
   if(dep == n) return;
   int i;
   for(i = from + 1; i < maxx; ++i)
      if(compare(i, dep))
      {
         ans[dep] = i;
         dfs(dep + 1, i);
         return;
      }
}
int main()
{
   ifstream cin ("hamming.in", ios::in);
   ofstream cout ("hamming.out", ios::out);
   ios::sync_with_stdio(false);
   int i;
   cin >> n >> b >> d;
   maxx = 1 << b;
   dfs(1, 0);
   for(i = 0; i < n - 1; ++i)
   {
      cout << ans[i];
      if(i % 10 == 9) cout << endl;
      else cout << ' ';
   }
   cout << ans[i] << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
