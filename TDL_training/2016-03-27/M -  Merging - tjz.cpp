#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxs = 8;
typedef long long LL;
typedef pair<LL, int> Node;
int n, m, a[maxn][maxs], num[maxn];
priority_queue<Node, vector<Node>, greater<Node> > Q;
LL f(int p, int x)
{
    LL ret = 0;
    for(int i = 0; i < maxs; ++i)
        ret = ret * x + a[p][i];
    //printf("f_%d(%d)=%lld\n", p, x, ret);
    return ret;
}
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < maxs; ++j)
            scanf("%d", a[i] + j);
        Q.push(make_pair(f(i, ++num[i]), i));
    }
    scanf("%d", &m);
    LL ans;
    for(int i = 0; i < m; ++i)
    {
        Node tmp = Q.top();
        Q.pop();
        ans = tmp.first;
        Q.push(make_pair(f(tmp.second, ++num[tmp.second]), tmp.second));
    }
    printf("%lld\n", ans);
    return 0;
}
