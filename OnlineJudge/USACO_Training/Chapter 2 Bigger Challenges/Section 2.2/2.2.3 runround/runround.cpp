/*
ID: tangjin2
LANG: C++
TASK: runround
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
int ans;
bool check()
{
   char tmp[10] = {};
   sprintf(tmp, "%d", ans);
   int i, flag = 0, len = strlen(tmp);
   bool used[10] = {}, visited[10] = {};
   for(i = 0; i < len; ++i)
      if(used[(int)tmp[i] - '0'])return false;
      else used[(int)tmp[i] - '0'] = true;
   for(i = 0; i < len; ++i)
   {
      flag = (flag + tmp[flag] - '0') % len;
      if(visited[flag]) return false;
      visited[flag] = true;
   }
   return true;
}
int main()
{
   ifstream cin ("runround.in", ios::in);
   ofstream cout ("runround.out", ios::out);
   ios::sync_with_stdio(false);
   cin >> ans;
   while(++ans)
      if(check())
      {
         cout << ans << endl;
         break;
      }
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
