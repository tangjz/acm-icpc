/*
ID: tangjin2
LANG: C++
TASK: clocks
*/
#include <fstream>
#include <iostream>
using namespace std;
const int check[9][9]={
{1,1,0,1,1,0,0,0,0},
{1,1,1,0,0,0,0,0,0},
{0,1,1,0,1,1,0,0,0},
{1,0,0,1,0,0,1,0,0},
{0,1,0,1,1,1,0,1,0},
{0,0,1,0,0,1,0,0,1},
{0,0,0,1,1,0,1,1,0},
{0,0,0,0,0,0,1,1,1},
{0,0,0,0,1,1,0,1,1}};
int data[9]={},way[1000]={},answer[1001]={},len=1000,number[9]={};
void dfs(int dep)
{
   if(dep > len)return;
   int x, y;
   for(x = 0; x < 9; ++x) if(data[x]) break;
   if(x >= 9)
   {
      len = dep - 1;
      for(x = 1; x <= len; ++x) answer[x] = way[x] + 1;
   }
   else
      for(x = way[dep-1]; x < 9; x++)
      {
         if(number[x] == 3)continue;
         for(y = 0; y < 9; ++y) data[y] = (data[y] + check[x][y])%4;
         ++number[x];
         way[dep] = x;
         dfs(dep + 1);
         for(y = 0; y < 9; ++y) data[y] = (data[y] - check[x][y] + 4)%4;
         --number[x];
      }
}
int main()
{
   ifstream cin ("clocks.in", ios::in);
   ofstream cout ("clocks.out", ios::out);
   ios::sync_with_stdio(false);
   int i, j;
   for(i = 0; i < 9; ++i)
   {
      cin >> data[i];
      data[i] = data[i] / 3 % 4;
   }
   way[0] = 0;
   dfs(1);
   for(i = 1; i <= len - 1 ; ++i) cout << answer[i] << ' ';
   cout << answer[len] << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
