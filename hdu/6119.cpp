#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, m;
LL tmp, sum, ans;
pair<int, int> a[maxn];
bool cmp(pair<int, int> const &x, pair<int, int> const &y) {
    if(x.first == y.first)
        return x.second > y.second;
    return x.first < y.first;
}
int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &a[i].first, &a[i].second);
        sort(a, a + n, cmp);
        int sz = 0;
        for(int i = 0; i < n; ++i)
            if(!sz || a[i - 1].first != a[i].first) {
                if(sz && a[sz - 1].second >= a[i].first)
                    a[sz - 1].second = max(a[sz - 1].second, a[i].second);
                else
                    a[sz++] = a[i];
            }
        n = sz;
        ans = tmp = sum = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            sum += a[i].second - a[i].first + 1;
            if(j < i)
                tmp += a[i].first - a[i - 1].second - 1;
            for( ; j < i && tmp > m; ++j) {
                sum -= a[j].second - a[j].first + 1;
                tmp -= a[j + 1].first - a[j].second - 1;
            }
            if(tmp <= m)
                ans = max(ans, sum + m);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
