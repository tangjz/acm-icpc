class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.size();
        if(n > 12)
            return {};
        map<pair<int, int>, vector<pair<int, int> > > nxt;
        nxt[{0, n}] = {};
        for(int i = n - 1; i >= 0; --i) {
            if(s[i] == '0') {
                for(int k = 0; k < 4; ++k)
                    if(nxt.count({k, i + 1}))
                        nxt[{k + 1, i}].push_back({k, i + 1});
                continue;
            }
            for(int j = i, val = 0; j < n; ++j) {
                val = val * 10 + (s[j] - '0');
                if(val > 255)
                    break;
                for(int k = 0; k < 4; ++k)
                    if(nxt.count({k, j + 1}))
                        nxt[{k + 1, i}].push_back({k, j + 1});
            }
        }
        string path = string(n + 3, '0');
        vector<string> ret;
        function<void(int, int, int)> dfs = [&](int rem, int pos, int len) {
            if(!rem) {
                ret.push_back(path);
                return;
            }
            for(auto &it: nxt[{rem, pos}]) {
                int sta = len;
                if(len)
                    path[sta++] = '.';
                for(int i = pos; i < it.second; ++i)
                    path[sta++] = s[i];
                dfs(it.first, it.second, sta);
            }
        };
        dfs(4, 0, 0);
        return ret;
    }
};
