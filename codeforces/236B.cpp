#include <iostream>
using namespace std;
const int mod = 1 << 30;
int a, b, c, divnum[1000001] = {};
long long ans = 0;
bool used[10001] = {};
int main()
{
    int i, j, k;
    ios::sync_with_stdio(false);
    cin >> a >> b >> c;
    k = a * b * c;
    for(i = 1; i <= k; ++i)
        for(j = i; j <= k; j += i) ++divnum[j];
    for(i = 1; i <= a; ++i)
        for(j = 1; j <= b; ++j)
            for(k = 1; k <= c; ++k)
                ans = (ans + divnum[i * j * k]) % mod;
    cout << ans << endl;
    return 0;
}
