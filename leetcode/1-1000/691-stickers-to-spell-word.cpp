class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        const int maxd = 26;
        vector<int> pos(maxd, -1), ctr;
        sort(target.begin(), target.end());
        for(char ch: target) {
            int o = ch - 'a';
            if(pos[o] == -1) {
                pos[o] = ctr.size();
                ctr.push_back(0);
            }
            ++ctr[pos[o]];
        }
        int m = ctr.size();
        vector<bool> cov(m);
        vector<vector<int> > cand;
        for(auto &it: stickers) {
            int sum = 0;
            vector<int> vec(m);
            for(char ch: it) {
                int o = ch - 'a';
                if(pos[o] == -1)
                    continue;
                ++sum;
                ++vec[pos[o]];
                cov[pos[o]] = 1;
            }
            if(sum)
                cand.push_back(vec);
        }
        if(!*min_element(cov.begin(), cov.end()))
            return -1;
        int n = target.size();
        map<vector<int>, int> dp;
        vector<vector<int> > rep(n);
        function<int(int, int)> calc = [&](int dep, int sum) {
            if(!sum)
                return 0;
            auto it = dp.find(ctr);
            if(it == dp.end()) {
                rep[dep] = ctr;
                int best = sum;
                for(auto &vec: cand) {
                    int nxt = sum;
                    for(int i = 0; i < m; ++i) {
                        int com = min(vec[i], ctr[i]);
                        nxt -= com;
                        ctr[i] -= com;
                    }
                    if(nxt < sum)
                        best = min(best, calc(dep + 1, nxt) + 1);
                    ctr = rep[dep];
                }
                it = dp.insert({ctr, best}).first;
            }
            return it -> second;
        };
        return calc(0, n);
    }
};
