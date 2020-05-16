#include <iostream>
#include <algorithm>
using namespace std;
int n, k, num[50] = {};
int main()
{
   ios::sync_with_stdio(false);
   int i;
   cin >> n >> k;
   if(n < k) cout << "-1" << endl;
   else
   {
      for(i = 0; i < n; ++i) cin >> num[i];
      sort(num, num + n);
      cout << num[n - k] << ' ' << num[n - k] << endl;
   }
   return 0;
}
