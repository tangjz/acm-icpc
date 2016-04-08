#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> G[30001];
int p, cnt;
bool visited[30001] = {};
void dfs(int u)
{
    for(vector<int>::size_type i = 0; i < G[u].size(); ++i)
    {
        int v = G[u][i];
        if(!visited[v])
        {
            ++cnt;
            visited[v] = true;
            dfs(v);
        }
    }
}
int main()
{
    int c, n, u, v;
    ios::sync_with_stdio(false);
    cin >> p >> c >> n;
    while(c--)
    {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    while(n--)
    {
        cin >> u;
        for(vector<int>::size_type i = 0; i < G[u].size(); ++i)
            visited[G[u][i]] = true;
    }
    visited[1] = true;
    cnt = 1;
    dfs(1);
    cout << p - cnt << endl;
    return 0;
}
