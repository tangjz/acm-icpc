class Solution {
public:
    vector<int> shortestSeq(vector<int>& big, vector<int>& small) {
        int n = big.size(), m = small.size(), cnt = 0, ans = n + 1, pos = -1;
        unordered_map<int, int> ctr;
        for(int x: small)
            ctr[x] = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && cnt < m; ++j) {
                auto it = ctr.find(big[j]);
                if(it == ctr.end())
                    continue;
                cnt -= (it -> second) > 0;
                ++(it -> second);
                cnt += (it -> second) > 0;
            }
            if(cnt == m && ans > j - i) {
                ans = j - i;
                pos = i;
            }
            auto it = ctr.find(big[i]);
            if(it == ctr.end())
                continue;
            cnt -= (it -> second) > 0;
            --(it -> second);
            cnt += (it -> second) > 0;
        }
        if(pos == -1)
            return {};
        return {pos, pos + ans - 1};
    }
};
