/*
ID: tangjin2
LANG: C++
TASK: preface
*/
#include <fstream>
#include <iostream>
using namespace std;
const int num[3][10][7] = 
{{{0,0,0,0,0,0,0},{1,0,0,0,0,0,0},{2,0,0,0,0,0,0},{3,0,0,0,0,0,0},{1,1,0,0,0,0,0},{0,1,0,0,0,0,0},{1,1,0,0,0,0,0},{2,1,0,0,0,0,0},{3,1,0,0,0,0,0},{1,0,1,0,0,0,0}},
 {{0,0,0,0,0,0,0},{0,0,1,0,0,0,0},{0,0,2,0,0,0,0},{0,0,3,0,0,0,0},{0,0,1,1,0,0,0},{0,0,0,1,0,0,0},{0,0,1,1,0,0,0},{0,0,2,1,0,0,0},{0,0,3,1,0,0,0},{0,0,1,0,1,0,0}},
 {{0,0,0,0,0,0,0},{0,0,0,0,1,0,0},{0,0,0,0,2,0,0},{0,0,0,0,3,0,0},{0,0,0,0,1,1,0},{0,0,0,0,0,1,0},{0,0,0,0,1,1,0},{0,0,0,0,2,1,0},{0,0,0,0,3,1,0},{0,0,0,0,1,0,1}}};
const char ch[7] = {'I','V','X','L','C','D','M'};
int n, cnt[7] = {};
int main()
{
   ifstream cin ("preface.in", ios::in);
   ofstream cout ("preface.out", ios::out);
   ios::sync_with_stdio(false);
   int i, tmp, mod;
   cin >> n;
   for(i = 1; i <= n; ++i)
   {
      tmp = i;
      if(tmp >= 1000)
      {
         cnt[6] += tmp / 1000;
         tmp %= 1000;
      }
      if(tmp >= 100)
      {
         mod = tmp / 100;
         cnt[4] += num[2][mod][4];
         cnt[5] += num[2][mod][5];
         cnt[6] += num[2][mod][6];
         tmp %= 100;
      }
      if(tmp >= 10)
      {
         mod = tmp / 10;
         cnt[2] += num[1][mod][2];
         cnt[3] += num[1][mod][3];
         cnt[4] += num[1][mod][4];
         tmp %= 10;
      }
      cnt[0] += num[0][tmp][0];
      cnt[1] += num[0][tmp][1];
      cnt[2] += num[0][tmp][2];
   }
   for(i = 0; i < 7; ++i) if(cnt[i]) cout << ch[i] << ' ' << cnt[i] << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}