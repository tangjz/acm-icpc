#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
map<string,int> person, check;
int n, goal[1001] = {}, ans;
string name[1001] = {};
int main()
{
   ios::sync_with_stdio(false);
   int i, j;
   cin >> n;
   for(i = 0; i < n; ++i)
   {
      cin >> name[i] >> goal[i];
      person[name[i]] += goal[i];
   }
   ans = person[name[0]];
   for(i = 1; i < n; ++i) if(person[name[i]] > ans) ans = person[name[i]];
   for(i = 0; i < n; ++i)
   {
      check[name[i]] += goal[i];
      if(check[name[i]] >= ans && person[name[i]] == ans)
      {
         cout << name[i] << endl;
         break;
      }
   }
   return 0;
}
