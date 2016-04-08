/*
 * 网络最小割 -> 网络最大流 ? TLE...
 * 平面图最小割 -> 对偶图最短路 ? Just do it!
 */
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
typedef priority_queue<edge, vector<edge>, greater<edge> > MinPQueue;
const int INF = 0x3f3f3f3f;
int n, m, t;
MinPQueue q;
vector<int> d;
vector<bool> visited;
vector<edge> G[2000001] = {};
int main()
{
    int i, j, u, v, maxn, tmp;
    ios::sync_with_stdio(false);
    cin >> n >> m;
//special judge
    if(n == 1)
    {
        cin >> j;
        for(i = 2; i < m; ++i) cin >> tmp, j = min(j, tmp);
        cout << j << endl;
        return 0;
    }
    if(m == 1)
    {
        cin >> j;
        for(i = 2; i < n; ++i) cin >> tmp, j = min(j, tmp);
        cout << j << endl;
        return 0;
    }
//calculate the number of point
    t = (n - 1) * (m - 1) * 2 + 1;
//run step 1
    for(i = 1; i < m; ++i) cin >> tmp, G[i * 2].push_back(make_pair(tmp, t));
    for(i = 1; i < n - 1; ++i)
        for(j = 1; j < m; ++j) cin >> tmp, G[i * (m - 1) * 2 + j * 2].push_back(make_pair(tmp, (i - 1) * (m - 1) * 2 + j * 2 - 1));
    for(i = 1; i < m; ++i) cin >> tmp, G[0].push_back(make_pair(tmp, (n - 2) * (m - 1) * 2 + i * 2 - 1));
//run step 2
    for(i = 0; i < n - 1; ++i)
    {
        cin >> tmp, G[0].push_back(make_pair(tmp, i * (m - 1) * 2 + 1));
        for(j = 1; j < m - 1; ++j) cin >> tmp, G[i * (m - 1) * 2 + j * 2].push_back(make_pair(tmp, i * (m - 1) * 2 + j * 2 + 1));
        cin >> tmp, G[(i + 1) * (m - 1) * 2].push_back(make_pair(tmp, t));
    }
//run step 3
    for(i = 0; i < n - 1; ++i)
        for(j = 1; j < m; ++j) cin >> tmp, G[i * (m - 1) * 2 + j * 2 - 1].push_back(make_pair(tmp, i * (m - 1) * 2 + j * 2));
//run dijkstra
    d.assign(t + 1, INF);
    visited.assign(t + 1, false);
    d[0] = 0;
    visited[0] = true;
    maxn = G[0].size();
    for(i = 0; i < maxn; ++i) d[G[0][i].second] = min(d[G[0][i].second], G[0][i].first);
    for(i = 0; i <= t; ++i) q.push(make_pair(d[i], i));
    for(i = 2; i < t; ++i)
    {
        do
        {
            u = q.top().second;
            q.pop();
        } while(visited[u]);
        visited[u] = true;
        maxn = G[u].size();
        for(j = 0; j < maxn; ++j)
        {
            tmp = d[u] + G[u][j].first;
            v = G[u][j].second;
            if(tmp < d[v])
            {
                d[v] = tmp;
                q.push(make_pair(tmp, v));
            }
        }
    }
    cout << d[t] << endl;
    return 0;
}
