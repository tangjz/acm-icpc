#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

bool solve() {
    i64 n;
    if(scanf("%lld", &n) == EOF || n == -1)
        return 0;
    i64 nn = n;
    vector<int> dig;
    for(++n; n > 0; dig.push_back(n % 5), n /= 5);

    int len = dig.size();
    vector<i64> pw = {1};
    for(int i = 1; i <= len; ++i)
        pw.push_back(pw.back() * 5);

    i64 ans = 0;
    for(int i = len - 1, c = 0; i >= 0; --i) {
        if(dig[i] > 0) {
            int half = i >> 1;
            i64 odd = (pw[half] >> 1) * pw[i - half], even = pw[i] - odd;
            int c1 = i & 1 ? dig[i] >> 1 : 0, c0 = dig[i] - c1;
            if(c & 1)
                swap(c0, c1);
            ans += c1 * odd + c0 * even;
        }
        c ^= i & 1 ? dig[i] & 1 : 0;
    }
    printf("%lld\n", ans);
    return 1;
}

int main() {
    while(solve());
    return 0;
}
