#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)2e4 + 1;

class RangeModule {
    map<int, pair<int, int> > seg;
public:
    void init() {
        seg.clear();
    }
    
    void addRange(int left, int right, int offset) { // [left, right): offset
        if(queryRange(left, right) == offset)
            return;
        removeRange(left, right);
        auto it = seg.upper_bound(left);
        if(it != seg.end() && it -> first <= right && it -> second.second == offset) {
            right = it -> second.first;
            // printf("erase %d %d %d\n", it -> first, it -> second.first, it -> second.second);
            it = seg.erase(it);
        }
        if(it != seg.begin() && (--it) -> second.first >= left && it -> second.second == offset) {
            left = it -> first;
            // printf("erase %d %d %d\n", it -> first, it -> second.first, it -> second.second);
            seg.erase(it);
        }
        // printf("insert %d %d %d\n", left, right, offset);
        seg.insert({left, {right, offset}});
    }
    
    int queryRange(int left, int right) { // [left, right): same ? offset : INT_MAX
        auto it = seg.upper_bound(left);
        return it != seg.begin() && (--it) -> second.first >= right ? it -> second.second : INT_MAX;
    }
    
    void removeRange(int left, int right) { // clean [left, right)
        for(auto it = seg.upper_bound(left); it != seg.end() && it -> first < right; ) {
            pair<int, pair<int, int> > rem = {right, it -> second};
            // printf("erase %d %d %d\n", it -> first, it -> second.first, it -> second.second);
            it = seg.erase(it);
            if(rem.first < rem.second.first) {
                // printf("insert %d %d %d\n", rem.first, rem.second.first, rem.second.second);
                seg.insert(rem);
                break;
            }
        }
        auto it = seg.upper_bound(left);
        if(it != seg.begin() && (--it) -> second.first > left) {
            pair<int, pair<int, int> > rem1 = {it -> first, {left, it -> second.second}};
            pair<int, pair<int, int> > rem2 = {right, it -> second};
            // printf("erase %d %d %d\n", it -> first, it -> second.first, it -> second.second);
            seg.erase(it);
            if(rem1.first < rem1.second.first) {
                // printf("insert %d %d %d\n", rem1.first, rem1.second.first, rem1.second.second);
                seg.insert(rem1);
            }
            if(rem2.first < rem2.second.first) {
                // printf("insert %d %d %d\n", rem2.first, rem2.second.first, rem2.second.second);
                seg.insert(rem2);
            }
        }
    }
} RM;

int main() {
    int n, q;
    static int a[maxn];
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    RM.init();
    scanf("%d", &q);
    while(q--) {
        int typ, u, v, w;
        scanf("%d%d", &typ, &u);
        if(typ == 2) {
            v = RM.queryRange(u, u + 1);
            v < INT_MAX && (v += u);
            printf("%d\n", 1 <= v && v <= n ? a[v] : -1);
            continue;
        }
        scanf("%d%d", &v, &w);
        tie(u, w) = make_pair(w, w + u - 1);
        tie(v, w) = make_pair(w, v - u);
        RM.addRange(u, v + 1, w);
    }
    return 0;
}
