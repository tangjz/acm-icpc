/*
 * 轮状病毒的方案数满足 F(n) = 3 * F(n - 1) + F(n - 2) + 2 (可用基尔霍夫矩阵证明该递推式)
 * 其中F(1) = 1, F(2) = 5
 */
#include <iostream>
using namespace std;
struct node{int num[1000], len;} f[101]={};
int n;
int main()
{
   ios::sync_with_stdio(false);
   int i, j;
   cin >> n;
   f[1].num[0] = f[1].len = f[2].len = 1;
   f[2].num[0] = 5;
   for(i = 3; i <= n; ++i)
   {
      f[i].len = f[i - 1].len;
      for(j = 0; j < f[i].len; ++j) f[i].num[j] = f[i - 1].num[j] * 3;
      f[i].num[0] += 2;
      for(j = 0; j < f[i].len; ++j)
         if(f[i].num[j] > 9)
         {
            f[i].num[j + 1] += f[i].num[j] / 10;
            f[i].num[j] %= 10;
         }
      if(f[i].num[f[i].len]) ++f[i].len;
      for(j = 0; j < f[i].len; ++j)
      {
         if(f[i].num[j] < f[i - 2].num[j])
         {
            f[i].num[j] += 10;
            --f[i].num[j + 1];
         }
         f[i].num[j] -= f[i - 2].num[j];
      }
      if(!f[i].num[f[i].len - 1]) --f[i].len;
   }
   for(i = f[n].len - 1; i >= 0; --i) cout << f[n].num[i];
   cout << endl;
   return 0;
}
