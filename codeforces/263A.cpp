#include <iostream>
using namespace std;
int abs_abs(int x, int y){if(x > y) return x - y; return y - x;}
int main()
{
   ios::sync_with_stdio(false);
   int num, sum = 25;
   while(sum--)
   {
      cin >> num;
      if(num)
      {
         cout << abs_abs(sum / 5, 2) + abs_abs(sum % 5, 2) << endl;
         break;
      }
   }
   return 0;
}
