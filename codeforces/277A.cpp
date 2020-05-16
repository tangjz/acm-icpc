#include <iostream>
using namespace std;
int n, m, father[101] = {}, ans = 0, cnt = 0;
bool f[101][101] = {};
int find(int x)
{
    if(father[x] != x) return father[x] = find(father[x]);
    return x;
}
bool check(int x, int y)
{
   x = find(x);
   y = find(y);
   if(x == y) return false;
   father[x] = y;
   return true;
}
int main()
{
    int i, j, k;
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(i = 1; i <= n; ++i) father[i] = i;
    for(i = 1; i <= n; ++i)
    {
        cin >> j;
        while(j--)
        {
            cin >> k;
            f[i][k] = true;
            cnt += f[i][k];
        }
    }
    for(i = 1; i <= n; ++i)
        for(j = i + 1; j <= n; ++j)
            for(k = 1; k <= m; ++k)
                if(f[i][k] && f[j][k]) ans += check(i, j);
    if(!cnt) cout << n << endl;
    else cout << n - ans - 1 << endl;
    return 0;
}
