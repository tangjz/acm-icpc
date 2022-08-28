class Solution {
public:
    bool wordPatternMatch(string pattern, string s) {
        unordered_map<char, int> pos;
        for(char ch: pattern)
            pos.insert({ch, pos.size()});
        int m = pos.size(), n = pattern.size(), q = s.size();
        vector<int> seq, ctr(m), path(m);
        seq.reserve(n);
        for(char ch: pattern) {
            seq.push_back(pos[ch]);
            ++ctr[seq.back()];
        }
        int sum = 0;
        function<bool(int)> dfs = [&](int dep) -> bool {
            if(dep == m) {
                if(sum != q)
                    return 0;
                unordered_set<string> cand;
                vector<string> rep(m);
                for(int i = 0, sta = 0; i < n; ++i) {
                    int j = seq[i];
                    if(rep[j].empty()) {
                        rep[j] = s.substr(sta, path[j]);
                        if(!cand.insert(rep[j]).second)
                            return 0;
                    } else if(rep[j] != s.substr(sta, path[j])) {
                        return 0;
                    }
                    sta += path[j];
                }
                return 1;
            }
            int pre = sum;
            for(int i = 1; (sum += ctr[dep]) <= q; ++i) {
                path[dep] = i;
                if(dfs(dep + 1))
                    return 1;
            }
            sum = pre;
            return 0;
        };
        return dfs(0);
    }
};
