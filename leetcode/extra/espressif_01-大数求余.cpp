#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    string buf;
    cin >> n >> m >> buf;
    int ans = 0;
    for(char ch: buf) {
        int x = -1;
        if(ch >= '0' && ch <= '9') {
            x = ch - '0';
        } else if(ch >= 'a' && ch <= 'z') {
            x = ch - 'a' + 10;
        }
        if(x < 0 || x >= n)
            break;
        ans = (ans * n + x) % m;
    }
    printf("%d\n", ans);
    return 0;
}
