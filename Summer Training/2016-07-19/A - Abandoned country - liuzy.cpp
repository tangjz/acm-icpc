#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 110000, EMAX = 3100000;

struct Edge
{
    int x;
    int y;
    int w;
    int next;
};

int T, N, M, V[NMAX], eid;
int father[NMAX], use[EMAX], son[NMAX], stamp, pre[NMAX], t[NMAX], in[NMAX];
Edge E[EMAX];
long long ans1, ans2;
vector<pair<int, int> > S;
queue<int> Q;

void insert(int x, int y, int w)
{
    E[++eid] = {x, y, w, V[x]};
    V[x] = eid;
}

int find(int x)
{
    int p, tmp;
    for(p = x;father[p] >= 0;p = father[p]);
    for(;x != p;)
    {
        tmp = father[x];
        father[x] = p;
        x = tmp;
    }
    return p;
}

void Union(int x, int y)
{
    int X = find(x), Y = find(y);
    if(X == Y)
        return;
    if(father[X] > father[Y])
        swap(X, Y);
    father[X] += father[Y];
    father[Y] = X;
}

void BFS()
{
    int x, i;
    pre[1] = 0;
    Q.push(1);
    in[1] = 1;
    while(!Q.empty())
    {
        x = Q.front();
        Q.pop();
        t[++stamp] = x;
        for(i = V[x];i;i = E[i].next)
        {
            if(use[i] && !in[E[i].y])
            {
                pre[E[i].y] = i;
                Q.push(E[i].y);
                in[E[i].y] = 1;
            }
        }
    }
    for(i = stamp;i;i -= 1)
    {
        x = t[i];
        son[x] += 1;
        ans2 += (long long)son[x] * E[pre[x]].w * (N - son[x]);
        son[E[pre[x]].x] += son[x];
    }
}

int main()
{
    int t, i, x, y, w;
    scanf("%d", &T);
    for(t = 1;t <= T;t += 1)
    {
        memset(father, ~0u, sizeof(father));
        memset(V, 0, sizeof(V));
        memset(pre, 0, sizeof(pre));
        memset(in, 0, sizeof(in));
        memset(son, 0, sizeof(son));
        memset(use, 0, sizeof(use));
        stamp = eid = ans1 = ans2 = 0;
        S.clear();
        //S.erase(S.begin(), S.end());
        scanf("%d %d", &N, &M);
        for(i = 1;i <= M;i += 1)
        {
            scanf("%d %d %d", &x, &y, &w);
            insert(x, y, w);
            S.push_back(make_pair(w, eid));
        }
        sort(S.begin(), S.end());
        for(i = 0;i < M;i += 1)
        {
            x = E[S[i].second].x;
            y = E[S[i].second].y;
            w = E[S[i].second].w;
            if(find(x) != find(y))
            {
                Union(x, y);
                ans1 += w;
                use[S[i].second] = 1;
                insert(y, x, w);
                use[eid] = 1;
            }
        }
        BFS();
        printf("%I64d %.2f\n", ans1, N == 1?0.0:ans2 / (double(N) * (N - 1) / 2));
    }
    exit(0);
}
