/*
 * DP: f[时间][能力] 注意初始化后按照决策顺序顺推! 
 * first : f[i + 1][j] = max(f[i + 1][j], f[i][j]) 直接继承 
 * second: f[i + cost[k]][j] = max{f[i][j] + 1}
 *         用cost[k]时间滑雪1次 cost[k]为能力下限为k的最短滑雪时间 
 * third : f[i + l[j]][a[j]] = max{f[i][j]}, i = m[j]
 *         用l[j]时间学习能力至a[j]
 */
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Node
{
    int need, time;
    bool operator < (const Node& r) const
    {
        if(need != r.need) return need < r.need;
        return time < r.time;
    }
} b[10001] = {};
int t, s, n, f[10002][101] = {}, ans;
int m[101] = {}, l[101] = {}, a[101] = {}, cost[10001] = {};
vector<int> lesson[10001];
int main()
{
    ifstream cin ("ski.in", ios::in);
    ofstream cout ("ski.out", ios::out);
    ios::sync_with_stdio(false);
    int i, j;
    cin >> t >> s >> n;
    for(i = 1; i <= s; ++i)
    {
        cin >> m[i] >> l[i] >> a[i];
        lesson[m[i]].push_back(i);
    }
    for(i = 1; i <= n; ++i) cin >> b[i].need >> b[i].time;
    sort(b + 1, b + n + 1);
    cost[b[1].need] = b[1].time;
    for(i = 2; i <= n; ++i)
        cost[b[i].need] = min(cost[b[i - 1].need], b[i].time);
    for(i = 2; i <= 10000; ++i) if(!cost[i]) cost[i] = cost[i - 1];
    for(i = 1; i <= t; ++i)
        for(j = 1; j <= 100; ++j) f[i][j] = -1;
    f[1][1] = 0;
    for(i = 1; i <= t; ++i)
        for(j = 1; j <= 100; ++j) 
        {
            if(f[i][j] == -1) continue;
            f[i + 1][j] = max(f[i + 1][j], f[i][j]);
            if(i + cost[j] <= t + 1)
                f[i + cost[j]][j] = max(f[i + cost[j]][j], f[i][j] + 1);
            for(vector<int>::size_type k = 0; k < lesson[i].size(); ++k)
                if(i + l[lesson[i][k]] <= t + 1)
                    f[i + l[lesson[i][k]]][a[lesson[i][k]]] = max(f[i][j],
                    f[i + l[lesson[i][k]]][a[lesson[i][k]]]);
        }
    ans = f[t + 1][1];
    for(i = 2; i <= 100; ++i) ans = max(ans, f[t + 1][i]);
    cout << ans << endl;
    return 0;
}
