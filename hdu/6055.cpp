#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 501, maxs = 201;
int n, x[maxn], y[maxn], ans;
set<pair<int, int> > pos;
int main() {
    while(scanf("%d", &n) == 1) {
        set<pair<int, int>>().swap(pos);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", x + i, y + i);
            pos.insert(make_pair(x[i], y[i]));
        }
        ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                int dx = x[j] - x[i], dy = y[j] - y[i];
                if((pos.count(make_pair(x[i] - dy, y[i] + dx)) && pos.count(make_pair(x[j] - dy, y[j] + dx))))
                    ++ans;
                if((pos.count(make_pair(x[i] + dy, y[i] - dx)) && pos.count(make_pair(x[j] + dy, y[j] - dx))))
                    ++ans;
            }
        printf("%d\n", ans >> 2);
    }
    return 0;
}
