class Solution {
public:
    int flipLights(int n, int presses) {
        vector<int> pos[4];
        for(int i = 0; i < n; ++i) {
            pos[0].push_back(i);
            pos[i & 1 ? 2 : 1].push_back(i);
            if(i % 3 == 0)
                pos[3].push_back(i);
        }
        set<vector<bool> > sp;
        for(int i = 0; i < (1 << 4); ++i) {
            int cnt = __builtin_popcount(i);
            if(cnt > presses || ((presses - cnt) & 1))
                continue;
            vector<bool> vec(n);
            for(int j = 0, tmp = i; j < 4; ++j, tmp >>= 1) {
                if(!(tmp & 1))
                    continue;
                for(int x: pos[j])
                    vec[x] = !vec[x];
            }
            sp.insert(vec);
        }
        return sp.size();
    }
};
