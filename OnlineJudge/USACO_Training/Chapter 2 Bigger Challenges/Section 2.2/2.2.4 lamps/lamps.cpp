/*
ID: tangjin2
LANG: C++
TASK: lamps
*/
#include <bitset>
#include <fstream>
#include <iostream>
using namespace std;
const int transformed[] = {63, 42, 21, 36};
int n, c, i, j, k;
bool on[7] = {}, off[7] = {}, light[64] = {}, succeed = false;
void dfs(int level, int start, int cnt)
{
   if(level >= 5) return;
   if(cnt <= c)
   {
      for(i = 1; i <= 6; ++i)
         if(on[i] && !((start >> (6 - i)) & 1) || off[i] && ((start >> (6 - i)) & 1)) break;
      if(i > 6)
      {
         light[start] = true;
         succeed = true;
      }
   }
   dfs(level + 1, start ^ transformed[level], cnt + 1);
   dfs(level + 1, start, cnt);
}
int main()
{
   ifstream cin ("lamps.in", ios::in);
   ofstream cout ("lamps.out", ios::out);
   ios::sync_with_stdio(false);
   cin >> n >> c >> k;
   while(k != -1)
   {
      k = (k - 1)%6 + 1;
      on[k] = true;
      cin >> k;
   }
   cin >> k;
   while(k != -1)
   {
      k = (k - 1)%6 + 1;
      off[k] = true;
      cin >> k;
   }
   dfs(0, 63, 0);
   if(!succeed) cout<< "IMPOSSIBLE" << endl;
   else
      for(i = 0; i <= 63; ++i)
         if(light[i])
         {
            for(j = n / 6; j ; --j) cout << bitset<6>(i);
            if(n % 6 != 0)
            {
               k = i >> (6 - (n % 6));
               switch(n % 6)
               {
                  case 1:cout << bitset<1>(k); break;
                  case 2:cout << bitset<2>(k); break;
                  case 3:cout << bitset<3>(k); break;
                  case 4:cout << bitset<4>(k); break;
                  case 5:cout << bitset<5>(k);
               }
            }
            cout << endl;
         }
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
