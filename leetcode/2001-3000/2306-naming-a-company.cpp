class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        typedef long long LL;
        unordered_map<string, int> Hash;
        int n = ideas.size();
        vector<int> pre(n), suf(n), msk;
        for(int i = 0; i < n; ++i) {
            auto res = Hash.insert({ideas[i].substr(1), (int)Hash.size()});
            if(res.second)
                msk.push_back(0);
            suf[i] = res.first -> second;
            pre[i] = ideas[i][0] - 'a';
            msk[suf[i]] |= 1 << pre[i];
        }
        const int maxd = 26;
        vector<vector<int> > ctr(maxd, vector<int>(maxd + 1));
        for(int i = 0; i < n; ++i) {
            ++ctr[pre[i]][maxd];
            for(int j = 0; j < maxd; ++j)
                if((msk[suf[i]] >> j) & 1)
                    ++ctr[pre[i]][j];
        }
        LL ans = (LL)n * n;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < maxd; ++j)
                if((msk[suf[i]] >> j) & 1) {
                    ans -= ctr[j][maxd] * 2;
                    ans += ctr[j][pre[i]];
                }
        return ans;
    }
};
