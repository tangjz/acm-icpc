#include <iostream>
using namespace std;
int n;
long double pi, comb = 0.0, ans = 0.0;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    while(n--)
    {
        cin >> pi;
        ans += comb * pi * 2.0 + pi;
        comb = comb * pi + pi;
    }
    cout.precision(17);
    cout << ans << endl;
    return 0;
}
