class Solution {
public:
    bool differByOne(vector<string>& dict) {
        typedef long long LL;
        static const int seed0 = 29, mod0 = (int)1e9 + 7;
        static const int seed1 = 31, mod1 = (int)1e9 + 9;
        int n = dict[0].size();
        vector<pair<int, int> > pw(n);
        pw[0] = {1, 1};
        for(int i = 1; i < n; ++i) {
            pw[i].first = (LL)pw[i - 1].first * seed0 % mod0;
            pw[i].second = (LL)pw[i - 1].second * seed1 % mod1;
        }
        typedef unsigned int UL;
        typedef unsigned long long ULL;
        unordered_set<ULL> Hash;
        for(auto &buf: dict) {
            pair<int, int> hs = {};
            for(int i = n - 1; i >= 0; --i) {
                int o = buf[i] - 'a' + 1;
                hs.first = ((LL)hs.first * seed0 + o) % mod0;
                hs.second = ((LL)hs.second * seed1 + o) % mod1;
            }
            for(int i = 0; i < n; ++i) {
                int o = buf[i] - 'a' + 1;
                pair<int, int> tp = hs;
                tp.first = (tp.first - (LL)pw[i].first * o) % mod0;
                tp.second = (tp.second - (LL)pw[i].second * o) % mod1;
                ULL msk = (UL)(tp.first < 0 ? tp.first + mod0 : tp.first);
                msk = msk << 32 | (UL)(tp.second < 0 ? tp.second + mod1 : tp.second);
                if(!Hash.insert(msk).second)
                    return 1;
            }
        }
        return 0;
    }
};
