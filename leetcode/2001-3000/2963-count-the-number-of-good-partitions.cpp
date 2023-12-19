class Solution {
public:
    int numberOfGoodPartitions(vector<int>& A) {
        int n = A.size();
        unordered_map<int, pair<int, int> > hs;
        for(int i = 0; i < n; ++i) {
            int v = A[i];
            if(!hs.count(v)) {
                hs[v] = {i, i};
                continue;
            }
            hs[v].second = i;
        }
        vector<int> ctr(n);
        for(auto &it: hs) {
            ++ctr[it.second.first];
            --ctr[it.second.second];
        }
        const int mod = (int)1e9 + 7;
        int ways = 1;
        for(int i = 0; i + 1 < n; ++i) {
            if(!ctr[i])
                (ways <<= 1) >= mod && (ways -= mod);
            ctr[i + 1] += ctr[i];
        }
        return ways;
    }
};
