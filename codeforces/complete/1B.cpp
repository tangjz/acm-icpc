#include <iostream>
#include <algorithm>
using namespace std;
int n, flag, sum;
string ch;
int check()
{
   if(ch[0] != 'R') return 0;
   if(ch[1] < '0' || ch[1] > '9') return 0;
   int i = 2;
   while(ch[i] != '\0')
   {
      if(ch[i] == 'C') return i;
      ++i;
   }
   return 0;
}
void output(int now)
{
   if(!now)return;
   if(now % 26 == 0)
   {
      output(now / 26 - 1);
   cout << 'Z';
   }
   else
   {
      output(now / 26);
      cout << (char)(now % 26 +'A' - 1);
   }
}
int main()
{
   ios::sync_with_stdio(false);
   int i;
   cin >> n;
   while(n--)
   {
      ch.clear();
      cin >> ch;
      flag = check();
      sum = 0;
      if(flag)
      {
         i = flag + 1;
         while(ch[i] != '\0')
         {
            sum = sum * 10 + (int)ch[i] - '0';
            ++i;
         }
         output(sum);
         i = 1;
         while(i < flag)
         {
            cout << ch[i];
            ++i;
         }
         cout << endl;
      }
      else
      {
         i = 0;
         while(ch[i] >= 'A' && ch[i] <= 'Z')
         {
            sum = sum * 26 + (int)ch[i] - 'A' + 1;
            ++i;
         }
         cout << "R";
         while(ch[i] != '\0')
         {
            cout << ch[i];
            ++i;
         }
         cout << "C" << sum << endl;
      }
   }
   return 0;
}
