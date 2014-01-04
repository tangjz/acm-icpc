/*
ID: tangjin2
LANG: C++
TASK: subset
*/
#include <fstream>
#include <iostream>
using namespace std;
int n, sum;
unsigned int f[781] = {};
int main()
{
   ifstream cin ("subset.in", ios::in);
   ofstream cout ("subset.out", ios::out);
   ios::sync_with_stdio(false);
   cin >> n;
   sum = n * (n + 1) / 2;
   if(sum & 1) cout << '0' << endl;
   else
   {
      int i, j;
      f[0] = 1;
      for(i = 1; i <= n; ++i)
         for(j = sum / 2; j >= i; --j) f[j] += f[j - i];
      cout << f[sum / 2] / 2 << endl;
   }
   cin.clear();cout.clear();
   cin.close();cout.close();
   return 0;
}
