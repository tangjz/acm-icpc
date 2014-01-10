/*
ID: tangjin2
LANG: C++
TASK: ariprog
*/
#include<fstream>
#include<iostream>
#include<algorithm>
using namespace std;
int n, m, maxx, num[125001]={}, len=0, tmp, i, j, b;
bool used[125001]={}, flag=false;
int main()
{
   ifstream cin("ariprog.in", ios::in);
   ofstream cout("ariprog.out", ios::out);
   ios::sync_with_stdio(false);
   cin >> n >> m;
   maxx = 2 * m * m;
   for(i = 0; i <= m ; ++i)
      for(j = i; j <= m; ++j)
      {
         tmp = i * i + j * j;
         if(used[tmp]) continue;
         used[tmp] = true;
         num[len] = tmp;
         ++len;
      }
   sort(num, num + len);
   for(b = 1; b <= num[len - 1] / (n - 1); ++b)
    {
       for(i = 0; num[i] + (n - 1) * b <= maxx; ++i)
       {
          for(j = 0; j < n; ++j) if(!used[num[i] + j * b]) break;
          if(j < n) continue;
          cout << num[i] << ' ' << b << endl;
          flag = true;
       }
    }
   if(!flag) cout << "NONE" << endl;
   cin.clear();
   cin.close();
   cout.clear();
   cout.close();
   return 0;
}
