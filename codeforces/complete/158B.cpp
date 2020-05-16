#include <iostream>
#include <algorithm>
using namespace std;
int n, cnt[5] = {}, ans;
int main()
{
    int i;
    ios::sync_with_stdio(false);
    cin >> n;
    while(n--)
    {
        cin >> i;
        ++cnt[i];
    }
    ans = cnt[4];
    ans += cnt[3];
    cnt[1] = max(cnt[1] - cnt[3], 0);
    ans += cnt[2] >> 1;
    if(cnt[2] & 1) ++ans, cnt[1] = max(cnt[1] - 2, 0);
    ans += cnt[1] / 4 + !(cnt[1] % 4 == 0);
    cout << ans << endl;
    return 0;
}
