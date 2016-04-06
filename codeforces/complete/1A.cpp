#include <iostream>
using namespace std;
__int64 n, m, a;
int main()
{
   ios::sync_with_stdio(false);
   while(cin >> n >> m >> a) cout << (n / a + (n % a != 0)) * (m / a + (m % a != 0)) << endl;
   return 0;
}
