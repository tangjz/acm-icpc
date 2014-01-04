/*
ID: tangjin2
LANG: C++
TASK: sort3
*/
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
int n, a[1000] = {}, b[1000] = {}, num[4][4] = {}, ans = 0;
int main()
{
   ifstream cin ("sort3.in", ios::in);
   ofstream cout ("sort3.out", ios::out);
   ios::sync_with_stdio(false);
   int i;
   cin >> n;
   for(i = 0; i < n; ++i)
   {
      cin >> a[i];
      b[i] = a[i];
   }
   sort(b, b + n);
   for(i = 0; i < n; ++i) ++num[b[i]][a[i]];
   i = min(num[1][2], num[2][1]);
   num[1][2] -= i;
   num[2][1] -= i;
   ans += i;
   i = min(num[1][3], num[3][1]);
   num[1][3] -= i;
   num[3][1] -= i;
   ans += i;
   i = min(num[2][3], num[3][2]);
   num[2][3] -= i;
   num[3][2] -= i;
   ans += i;
   ans += max(num[1][2], num[2][1]) * 2;
   cout << ans << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
