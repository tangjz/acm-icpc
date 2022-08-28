#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<int> vals;
    scanf("%d", &n);
    for(int i = 0, x; i < n; ++i) {
        scanf("%d", &x);
        vals.push_back(x);
    }
    int ans = INT_MIN;
    for(int i = 1; i * 3 <= n; ++i) {
        if(n % i != 0)
            continue;
        vector<int> sum(i);
        for(int j = 0; j < n; ++j)
            sum[j % i] += vals[j];
        ans = max(ans, *max_element(sum.begin(), sum.end()));
    }
    printf("%d\n", ans);
    return 0;
}
