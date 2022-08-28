class Solution {
    pair<int, int> reduce(pair<int, int> val) {
        if(val.second < 0)
            val = {-val.first, -val.second};
        int com = gcd(abs(val.first), val.second);
        return {val.first / com, val.second / com};
    }
public:
    bool judgePoint24(vector<int>& cards) {
        int n = cards.size(), all = (1 << n) - 1;
        vector<vector<pair<int, int> > > cand(all + 1);
        for(int i = 0; i < n; ++i)
            cand[1 << i].push_back({cards[i], 1});
        for(int i = 1; i <= all; ++i) {
            if((i & -i) == i)
                continue;
            auto &ret = cand[i];
            for(int j = (i - 1) & i; j > 0; j = (j - 1) & i)
                for(auto &lft: cand[j])
                    for(auto &rht: cand[i ^ j]) {
                        ret.push_back(reduce({lft.first * rht.second + rht.first * lft.second, lft.second * rht.second}));
                        ret.push_back(reduce({lft.first * rht.second - rht.first * lft.second, lft.second * rht.second}));
                        ret.push_back(reduce({lft.first * rht.first, lft.second * rht.second}));
                        if(rht.first != 0)
                            ret.push_back(reduce({lft.first * rht.second, lft.second * rht.first}));
                    }
            sort(ret.begin(), ret.end());
            ret.erase(unique(ret.begin(), ret.end()), ret.end());
        }
        for(auto &val: cand[all])
            if(val.first == 24 && val.second == 1)
                return 1;
        return 0;
    }
};
