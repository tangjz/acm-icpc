#include <iostream>
using namespace std;
int n, s, t, line[101] = {}, ans = 0, tmp = 0;
int main()
{
    int i;
    ios::sync_with_stdio(false);
    cin >> n;
    for(i = 1; i <= n; ++i) cin >> line[i];
    cin >> s >> t;
    i = s;
    while(i != t)
    {
        tmp += line[i];
        ++i;
        if(i > n) i = 1;
    }
    while(i != s)
    {
        ans += line[i];
        ++i;
        if(i > n) i = 1;
    }
    if(tmp < ans) ans = tmp;
    cout << ans << endl;
    return 0;
}
