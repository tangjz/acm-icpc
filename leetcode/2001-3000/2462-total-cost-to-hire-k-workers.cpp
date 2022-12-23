class Solution {
public:
    long long totalCost(vector<int>& A, int m, int d) {
        typedef long long LL;
        int n = A.size(), L = 0, R = n; // [0, L), [R, n)
        LL ans = 0;
        set<pair<int, int> > sp;
        for(int i = 0; i < d && L < R; ++i, ++L)
            sp.insert({A[L], L});
        for(int i = 0; i < d && L < R; ++i, --R)
            sp.insert({A[R - 1], R - 1});
        while(m--) {
            pair<int, int> cur = *sp.begin();
            sp.erase(cur);
            ans += cur.first;
            if(L == R)
                continue;
            if(cur.second < L) {
                sp.insert({A[L], L});
                ++L;
            } else {
                sp.insert({A[R - 1], R - 1});
                --R;
            }
        }
        return ans;
    }
};
