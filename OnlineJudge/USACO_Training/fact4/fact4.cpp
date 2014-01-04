/*
ID: tangjin2
LANG: C++
TASK: fact4
*/
#include <fstream>
#include <iostream>
using namespace std;
const int mod = 1000000;
int n, i, ans;
int main()
{
   ifstream cin("fact4.in", ios::in);
   ofstream cout("fact4.out", ios::out);
   ios::sync_with_stdio(false);
   cin >> n;
   ans = 1;
   for(i = 2; i <= n; ++i)
   {
      ans *= i;
      ans %= mod;
      while(ans % 10 == 0) ans /= 10;
   }
   cout << ans % 10 << endl;
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
