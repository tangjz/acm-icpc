#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool solve() {
    int n;
    scanf("%d", &n);
    vector<int> seq[2];
    for(int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        seq[i & 1].push_back(x);
    }
    sort(seq[0].begin(), seq[0].end(), greater<int>());
    sort(seq[1].begin(), seq[1].end(), greater<int>());
    int las = 0;
    for(int i = 0; i < n; ++i) {
        int cur = seq[i & 1].back();
        seq[i & 1].pop_back();
        if(las > cur)
            return 0;
        las = cur;
    }
    return 1;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}