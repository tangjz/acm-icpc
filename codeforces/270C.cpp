#include <iostream>
using namespace std;
int n, k, a, ans = 1, tmp;
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    while(n--)
    {
        cin >> k >> a;
        if(a == 1) tmp = k + 1;
        else
        {
            tmp = k;
            while(a > 1)
            {
                a = (a - 1) / 4 + 1;
                ++tmp;
            }
        }
        if(ans < tmp) ans = tmp;
    }
    cout << ans << endl;
    return 0;
}
