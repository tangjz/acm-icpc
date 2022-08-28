#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e4 + 1, mod = 998244353;

int main() {
    int n, m, q;
    static int pos[maxn];
    static bool ban[maxn], used[maxn];
    scanf("%d%d%d", &m, &n, &q);
    memset(pos + 1, -1, m * sizeof(int));
    memset(ban + 1, 0, n * sizeof(bool));
    memset(used + 1, 0, m * sizeof(bool));
    while(q--) {
        int typ, x, y;
        scanf("%d%d", &typ, &x);
        switch(typ) {
            case 1: {
                scanf("%d", &y);
                if(!used[x] && (pos[x] == -1 || !ban[pos[x]]) && !ban[y])
                    pos[x] = y;
                break;
            }
            case 2: {
                ban[x] = 1;
                break;
            }
            case 3: {
                ban[x] = 0;
                break;
            }
            case 4: {
                if(used[x] || pos[x] == -1 || ban[pos[x]]) {
                    puts("-1");
                } else {
                    printf("%d\n", pos[x]);
                    pos[x] = -1;
                    used[x] = 1;
                }
                break;
            }
            case 5: {
                used[x] = 0;
                break;
            }
        }
    }

    return 0;
}
