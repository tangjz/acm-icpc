#include <iostream>
#include <algorithm>
using namespace std;
int n, x, y, num[1001][1001] = {}, d2[1001][1001] = {}, d5[1001][1001] = {};
char dr2[1001][1001] = {}, dr5[1001][1001] = {};
bool flag = false;
int calc(int x, int p)
{
   if(!x) return 1;
   int cnt = 0;
   while(x % p == 0)
   {
      ++cnt;
      x /= p;
   }
   return cnt;
}
void dp(int d[][1001], char dr[][1001], int p)
{
   int i, j;
   d[0][0] = calc(num[0][0], p);
   dr[0][0] = 'R';
   for(i = 1; i < n; ++i)
   {
      d[0][i] = d[0][i - 1] + calc(num[0][i], p);
      dr[0][i] = 'R';
   }
   for(i = 1; i < n; ++i)
      for(j = 0; j < n; ++j)
         if(!j)
         {
            d[i][j] = d[i - 1][j] + calc(num[i][j], p);
            dr[i][j] = 'D';
         }
         else if(d[i - 1][j] < d[i][j - 1])
         {
            d[i][j] = d[i - 1][j] + calc(num[i][j], p);
            dr[i][j] = 'D';
         }
         else
         {
            d[i][j] = d[i][j - 1] + calc(num[i][j], p);
            dr[i][j] = 'R';
         }
}
void print(char dr[][1001], int x, int y)
{
   if(!x && !y)return;
   if(dr[x][y] == 'D') print(dr, x - 1, y);
   else print(dr, x, y - 1);
   cout << dr[x][y];
}
int main()
{
   ios::sync_with_stdio(false);
   int i, j;
   cin >> n;
   for(i = 0; i < n; ++i)
      for(j = 0; j < n; ++j)
      {
         cin >> num[i][j];
         if(!num[i][j])
         {
            flag = true;
            x = i;
            y = j;
         }
      }
   dp(d2, dr2, 2); 
   dp(d5, dr5, 5);
   if(flag)
   {
      if(!d2[n - 1][n - 1])
      {
         cout << '0' << endl;
         print(dr2, n - 1, n - 1);
      }
      else if(!d5[n - 1][n - 1])
      {
         cout << '0' << endl;
         print(dr5, n - 1, n - 1);
      }
      else
      {
         cout << '1' << endl;
         for(i = 0; i < x; ++i) cout << 'D';
         for(i = 0; i < n - 1; ++i) cout << 'R';
         for(i = x; i < n - 1; ++i) cout << 'D';
      }
   }
   else if(d2[n - 1][n - 1] < d5[n - 1][n - 1])
   {
      cout << d2[n - 1][n - 1] << endl;
      print(dr2, n - 1, n - 1);
   }
   else
   {
      cout << d5[n - 1][n - 1] << endl;
      print(dr5, n - 1, n - 1);
   }
   cout << endl;
   return 0;
}
