#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<bool> vis(n);
    for(int i = 0; i < n; ++i) {
        int k = -1;
        for(int j = 0, x; j < n; ++j) {
            scanf("%d", &x);
            if(k == -1 && !vis[--x]) {
                k = x;
                vis[x] = 1;
            }
        }
        printf("%d%c", ++k, " \n"[i == n - 1]);
    }
    return 0;
}
