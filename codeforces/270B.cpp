#include <iostream>
using namespace std;
int n, a[100001] = {}, ans = 0;
int main()
{
    int i;
    ios::sync_with_stdio(false);
    cin >> n;
    for(i = 1; i <= n; ++i) cin >> a[i];
    for(i = 1; i < n; ++i) if(a[i] > a[i + 1]) ans = i;
    cout << ans << endl;
    return 0;
}
