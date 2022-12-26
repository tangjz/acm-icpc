#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, INF = 0x3f3f3f3f;
int t, n, m, a[maxn], b[maxn], ord[maxn];
bool cmp(int const &x, int const &y) {
    return a[x] < a[y] || (a[x] == a[y] && x < y);
}
struct Node {
    int fz, fm;
    bool operator < (Node const &t) const {
        return (LL)fz * t.fm < (LL)t.fz * fm;
    }
    void parse(int x, int y) {
        int r = __gcd(x, y);
        fz = x / r;
        fm = y / r;
    }
    void print() {
        printf("%d/%d\n", fz, fm);
    }
} f[maxn];
struct Event {
    int idx;
    bool operator < (Event const &t) const {
        return f[idx] < f[t.idx];
    }
};
set<int> sp;
set<Event> tim;
inline int left(int x) {
    set<int>::iterator it = sp.lower_bound(x);
    return it == sp.begin() ? *sp.rbegin() : *(--it);
}
inline int right(int x) {
    set<int>::iterator it = sp.upper_bound(x);
    return it == sp.end() ? *sp.begin() : *it;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        set<int>().swap(sp);
        set<Event>().swap(tim);
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            ord[i] = i;
        }
        sort(ord + 1, ord + n + 1, cmp);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", b + i);
            sp.insert(i);
        }
        for(int i = 1; i <= n; ++i) {
            int j = i == 1 ? n : i - 1;
            if(b[ord[j]] != b[ord[i]]) {
                int fz = a[ord[j]] - a[ord[i]], fm = b[ord[i]] - b[ord[j]];
                if(fm < 0) {
                    fz = -fz;
                    fm = -fm;
                }
                if(fz < 0)
                    fz += m;
                f[i].parse(fz, fm);
            } else {
                f[i].parse(a[ord[j]] == a[ord[i]] ? 0 : INF, 1);
            }
            tim.insert((Event){i});
        }
        while(1) {
            int pR = tim.begin() -> idx, pL = left(pR);
            // printf("%d %d: ", pL, pR); f[pR].print();
            if(sp.size() == 2) {
                f[pR].print();
                break;
            }
            if(ord[pL] < ord[pR]) { // erase pL
                tim.erase((Event){pL});
                sp.erase(pL);
                pL = left(pR);
            } else { // erase pR
                tim.erase((Event){pR});
                sp.erase(pR);
                pR = right(pL);
            }
            tim.erase((Event){pR});
            if(b[ord[pL]] != b[ord[pR]]) {
                int fz = a[ord[pL]] - a[ord[pR]], fm = b[ord[pR]] - b[ord[pL]];
                if(fm < 0) {
                    fz = -fz;
                    fm = -fm;
                }
                if(fz < 0)
                    fz += m;
                f[pR].parse(fz, fm);
            } else {
                f[pR].parse(a[ord[pL]] == a[ord[pR]] ? 0 : INF, 1);
            }
            tim.insert((Event){pR});
        }
    }
    return 0;
}
