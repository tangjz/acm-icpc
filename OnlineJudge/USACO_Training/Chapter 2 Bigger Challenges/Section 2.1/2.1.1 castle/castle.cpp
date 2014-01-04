/*
ID: tangjin2
LANG: C++
TASK: castle
*/
#include <fstream>
#include <iostream>
using namespace std;
int m, n, room[51][51] = {}, num[51][51] = {}, sum = 0, cnt[2501] = {}, tmp1, tmp2, max_castle = 0, max_delete = 0;
char flag;
void dfs(int x, int y)
{
   if(x < 1 || x > n || y < 1 || y > m || num[x][y]) return;
   num[x][y] = sum;
   ++cnt[sum];
   int tmp = 15 - room[x][y];
   if(tmp & 1) dfs(x, y - 1);
   if(tmp & 2) dfs(x - 1, y);
   if(tmp & 4) dfs(x, y + 1);
   if(tmp & 8) dfs(x + 1, y);
}
int main()
{
   ifstream cin ("castle.in", ios::in);
   ofstream cout ("castle.out", ios::out);
   ios::sync_with_stdio(false);
   int i, j;
   cin >> m >> n;
   for(i = 1; i <= n; ++i)
      for(j = 1; j <= m; ++j) cin >> room[i][j];
   for(i = 1; i <= n; ++i)
      for(j = 1; j <= m; ++j)
      {
         if(!num[i][j])
         {
            ++sum;
            dfs(i, j);
            if(cnt[sum] >= max_castle) max_castle = cnt[sum];
         }
      }
   cout << sum << endl;
   cout << max_castle << endl;
   for(i = 1; i <= m; ++i)
      for(j = n; j > 1 || n == 1 && j > 0; --j)
      {
         if(j >= 2 && num[j][i] != num[j-1][i] && cnt[num[j][i]] + cnt[num[j - 1][i]] > max_delete)
         {
            tmp1 = j;
            tmp2 = i;
            flag = 'N';
            max_delete = cnt[num[j][i]] + cnt[num[j - 1][i]];
         }
         if(i < m && num[j][i] != num[j][i + 1] && cnt[num[j][i]] + cnt[num[j][i + 1]] > max_delete)
         {
            tmp1 = j;
            tmp2 = i;
            flag = 'E';
            max_delete = cnt[num[j][i]] + cnt[num[j][i + 1]];
         }
      }
   cout << max_delete << endl;
   cout << tmp1 << ' ' << tmp2 << ' ' << flag << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
