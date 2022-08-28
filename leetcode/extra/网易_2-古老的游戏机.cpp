#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> ctr(n);
    while(m--) {
        int x;
        scanf("%d", &x);
        ++ctr[--x];
    }
    printf("%d\n", *min_element(ctr.begin(), ctr.end()));
    return 0;
}
