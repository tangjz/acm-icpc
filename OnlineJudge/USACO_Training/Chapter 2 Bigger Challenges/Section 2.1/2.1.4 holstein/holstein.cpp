/*
ID: tangjin2
LANG: C++
TASK: holstein
*/
#include <fstream>
#include <iostream>
using namespace std;
int v, goal[25] = {}, g, num[15][25] = {}, ans, tmp[15] = {}, output[15] = {};
void dfs(int dep, int from)
{
   if(dep > ans) return;
   int i, j;
   for(i = from; i < g; ++i)
   {
      for(j = 0; j < v; ++j) goal[j] -= num[i][j];
      tmp[dep - 1] = i;
      for(j = 0; j < v; ++j) if(goal[j] > 0) break;
      if(j < v) dfs(dep + 1, i + 1);
      else if(dep < ans || !output[0])
      {
         ans = dep;
         for(j = 0; j < ans; ++j) output[j] = tmp[j] + 1;
      }
      for(j = 0; j < v; ++j) goal[j] += num[i][j];
   }
}
int main()
{
   ifstream cin ("holstein.in", ios::in);
   ofstream cout ("holstein.out", ios::out);
   ios::sync_with_stdio(false);
   int i, j;
   cin >> v;
   for(i = 0; i < v; ++i) cin >> goal[i];
   cin >> g;
   for(i = 0; i < g; ++i)
      for(j = 0; j < v; ++j) cin >> num[i][j];
   ans = g;
   dfs(1, 0);
   cout << ans;
   for(i = 0; i < ans; ++i) cout << ' ' << output[i];
   cout << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
} 
