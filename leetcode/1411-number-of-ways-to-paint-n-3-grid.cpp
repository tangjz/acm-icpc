class Solution {
public:
    int numOfWays(int n) {
        map<vector<int>, int> Hash;
        function<void(int, vector<int> &)> dfs = [&](int dep, vector<int> &cur) {
            if(dep == 3) {
                if(!Hash.count(cur))
                    Hash.insert(make_pair(cur, (int)Hash.size()));
            } else {
                int las = cur.empty() ? -1 : cur.back();
                for(int i = 0; i < 3; ++i)
                    if(i != las) {
                        cur.push_back(i);
                        dfs(dep + 1, cur);
                        cur.pop_back();
                    }
            }
        };
        vector<int> temp;
        dfs(0, temp);
        int m = (int)Hash.size();
        vector<vector<int> > trans(m, vector<int>());
        for(auto &it : Hash) {
            auto &vec0 = it.first;
            for(auto &jt : Hash) {
                auto &vec1 = jt.first;
                bool chk = 1;
                for(int i = 0; chk && i < 3; ++i)
                    chk &= vec0[i] != vec1[i];
                if(chk)
                    trans[it.second].push_back(jt.second);
            }
        }
        auto mod_inc = [](int &x, int y) {
            const int mod = (int)1e9 + 7;
            (x += y) >= mod && (x -= mod);
        };
        vector<int> f(m, 1), g;
        for(int i = 1; i < n; ++i) {
            g = move(f);
            vector<int>(m, 0).swap(f);
            for(int j = 0; j < m; ++j) {
                if(!g[j])
                    continue;
                for(int &k : trans[j])
                    mod_inc(f[k], g[j]);
            }
        }
        int ans = 0;
        for(int i = 0; i < m; ++i)
            mod_inc(ans, f[i]);
        return ans;
    }
};
