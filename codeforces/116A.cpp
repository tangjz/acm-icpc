#include <iostream>
using namespace std;
int n, a, b, ans = 0, tmp = 0;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    while(n--)
    {
        cin >> a >> b;
        tmp += b - a;
        ans = max(ans, tmp);
    }
    cout << ans << endl;
    return 0;
}
