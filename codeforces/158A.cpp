#include <iostream>
using namespace std;
int n, k, goal[51] = {};
int main()
{
    int i;
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for(i = 1; i <= n; ++i) cin >> goal[i];
    if(goal[k]) while(goal[k] == goal[k + 1]) ++k;
    else while(k && !goal[k]) --k;
    cout << k << endl;
    return 0;
}
