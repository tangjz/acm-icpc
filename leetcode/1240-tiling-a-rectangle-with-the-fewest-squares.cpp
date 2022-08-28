class Solution {
    void dfs(int dep, vector<int> &cnt, int n, int m, map<vector<int>, int> &Hash, int &ans) {
        if(dep >= ans)
            return;
        auto it = Hash.find(cnt);
        if(it != Hash.end()) {
            if(dep > it -> second)
                return;
            it -> second = dep;
        } else {
            Hash.insert({cnt, dep});
        }
        int pos = 0;
        for(int i = 1; i < n; ++i)
            if(cnt[i] < cnt[pos])
                pos = i;
        int len = 1;
        for( ; pos + len < n && cnt[pos] == cnt[pos + len]; ++len);
        if(len == n && cnt[0] == m) {
            ans = dep;
            return;
        }
        for(int i = min(len, m - cnt[pos]); i >= 1; --i) {
            for(int j = 0; j < i; ++j)
                cnt[pos + j] += i;
            dfs(dep + 1, cnt, n, m, Hash, ans);
            for(int j = 0; j < i; ++j)
                cnt[pos + j] -= i;
        }
    }
public:
    int tilingRectangle(int n, int m) {
        if(n > m)
            swap(n, m);
        static map<pair<int, int>, int> His;
        auto it = His.find({n, m});
        if(it != His.end())
            return it -> second;
        int ans = n * m;
        vector<int> cnt(n);
        static map<vector<int>, int> Hash;
        dfs(0, cnt, n, m, Hash, ans);
        His.insert({{n, m}, ans});
        return ans;
    }
};
