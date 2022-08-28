class Solution {
public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        int n = target.size(), ans = n, best = (1 << n) - 1;
        vector<set<int> > cand(n + 1);
        for(auto &buf: dictionary) {
            if(buf.size() != n)
                continue;
            int msk = 0;
            for(int i = 0; i < n; ++i)
                msk |= (target[i] != buf[i]) << i;
            assert(msk);
            cand[0].insert(msk);
        }
        vector<int> sz(n + 1);
        for(int i = 1; i <= n; ++i)
            sz[i] = to_string(i).size();
        function<void(int, int, int)> dfs = [&](int dep, int low, int msk) {
            // printf("dfs %d %d %d: cand %d\n", dep, low, msk, (int)cand[dep].size());
            int len = 0;
            for(int i = 0, j, tmp = msk; i < n; ) {
                int cur = tmp & 1;
                for(j = i; i < n && (tmp & 1) == cur; ++i, tmp >>= 1);
                if(cur) {
                    len += i - j;
                } else {
                    // printf("sz %d\n", i - j);
                    len += sz[i - j];
                }
            }
            // printf("len %d\n", len);
            if(len >= ans)
                return;
            if(cand[dep].empty()) {
                ans = len;
                best = msk;
                return;
            }
            int nxt = 0;
            for(int x: cand[dep])
                nxt |= x & ~msk;
            // printf("nxt %d\n", nxt);
            for(int i = low; i < n; ++i) {
                if(!((nxt >> i) & 1))
                    continue;
                int nmsk = msk | (1 << i);
                cand[dep + 1].clear();
                for(int x: cand[dep])
                    if(!(x & nmsk))
                        cand[dep + 1].insert(x);
                dfs(dep + 1, i + 1, nmsk);
            }
        };
        dfs(0, 0, 0);
        string ret = "";
        for(int i = 0, j, tmp = best; i < n; ) {
            int cur = tmp & 1;
            for(j = i; i < n && (tmp & 1) == cur; ++i, tmp >>= 1);
            if(cur) {
                ret += target.substr(j, i - j);
            } else {
                ret += to_string(i - j);
            }
        }
        return ret;
    }
};
