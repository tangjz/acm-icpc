#include <bits/stdc++.h>
using namespace std;

int main() {
    int r, c;
    assert(scanf("%d%d", &r, &c) == 2);
    assert(r > 0 && r == c);
    int n = r;
    const int INF = 0x3f3f3f3f;
    vector<vector<int> > dis(n, vector<int>(n, INF));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            static char buf[11];
            scanf("%s", buf);
            if(buf[0] == 'a')
                continue;
            dis[i][j] = stoi(buf);
        }
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            if(i == j)
                continue;
            if(dis[i][j] < INF) {
                printf("The shortest distance between %d and %d is: %d\n", i, j, dis[i][j]);
            } else {
                printf("There is no path between %d and %d\n", i, j);
            }
        }
    return 0;
}
