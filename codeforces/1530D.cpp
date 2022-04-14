#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 9;
void solve() {
    int n, cnt = 0;
    // n = rand() % 10 + 2;
    scanf("%d", &n);
    vector<int> pre(n, -1), nxt(n), remP, remN;
    for(int i = 0; i < n; ++i) {
        // nxt[i] = rand() % (n - 1) + 1;
        // if(nxt[i] >= i)
        //     ++nxt[i];
        scanf("%d", &nxt[i]);
        --nxt[i];
        if(pre[nxt[i]] == -1) {
            pre[nxt[i]] = i;
            ++cnt;
        } else {
            remN.push_back(i);
        }
    }
    for(int i = 0; i < n; ++i)
        if(pre[i] == -1)
            remP.push_back(i);
    if(cnt == n - 1 && remP.back() == remN.back()) {
        int i = remN.back();
        remN.back() = pre[nxt[i]];
        pre[nxt[i]] = i;
    }
    int sz = (int)remP.size();
    sort(remP.begin(), remP.end());
    sort(remN.begin(), remN.end(), greater<int>());
    for(int i = 0; i < sz; ++i) {
        if(remP[i] != remN[i])
            continue;
        swap(remP[i], remP[i > 0 ? i - 1 : i + 1]);
    }
    for(int i = 0; i < sz; ++i) {
        int u = remP[i], v = remN[i];
        pre[u] = v;
        nxt[v] = u;
    }
    printf("%d\n", cnt);
    for(int i = 0; i < n; ++i)
        printf("%d%c", nxt[i] + 1, " \n"[i == n - 1]);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
	}
	return 0;
}