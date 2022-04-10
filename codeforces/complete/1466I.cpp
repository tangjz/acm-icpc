#include <bits/stdc++.h>
using namespace std;
const int maxn = 201;
bitset<maxn> cur;
unordered_map<int, unordered_map<bitset<maxn>, bool> > vis;
char buf[maxn << 1 | 1], rsp[5];
bool ask(int x, char buf[]) {
    auto it = vis[x].find(cur);
    if(it != vis[x].end())
        return it -> second;
    printf("%d %s\n", x, buf);
    fflush(stdout);
    scanf("%s", rsp);
    return vis[x][cur] = rsp[0] == 'y';
}
int main() {
    int n, b;
    scanf("%d%d", &n, &b);
    for(int i = 0; i < n + b; ++i) {
        buf[i] = '1';
        if(i < b && buf[i] == '1')
            cur.set(i);
    }
    deque<int> cand;
    for(int i = 1; i <= n; ++i) {
        cand.push_back(i);
        vis[i][cur] = 0;
    }
    buf[0] = '0';
    cur.reset(0);
    for(int c = 0; c - (int)cand.size() < b - 1; ) {
        char ch = buf[b];
        buf[b] = '\0';
        bool res = ask(cand.front(), buf);
        buf[b] = ch;
        if(res) {
            for( ; buf[c] == '1'; --c)
                cand.pop_back();
            buf[c] = '1';
            if(c < b)
                cur.set(c);
        } else {
            buf[++c] = '0';
            if(c < b)
                cur.reset(c);
            cand.push_back(cand.front());
            cand.pop_front();
        }
    }
    buf[b] = '\0';
    printf("0 %s\n", buf);
    return 0;
}