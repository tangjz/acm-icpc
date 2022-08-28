#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1, maxd = 4, maxc = 256;

int main() {
    static int st = 0, tim[maxc + 1] = {};
    static char buf[maxd + 1][maxn];
    for(int i = 0; i < maxd; ++i)
        scanf("%s", buf[i]);
    for(int i = 0; buf[0][i]; ++i) {
        ++st;
        char ch = '\0';
        for(int j = 0; j < maxd; ++j) {
            if(tim[buf[j][i]] == st) {
                if(ch == '\0') {
                    ch = buf[j][i];
                } else if(ch != buf[j][i]) {
                    ch = '\0';
                    break;
                }
            }
            tim[buf[j][i]] = st;
        }
        if(ch == '\0') {
            puts("Input Error");
            return 0;
        }
        buf[0][i] = ch;
    }
    puts(buf[0]);
    return 0;
}
