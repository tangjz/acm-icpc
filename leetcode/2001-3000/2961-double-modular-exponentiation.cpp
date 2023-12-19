class Solution {
public:
    vector<int> getGoodIndices(vector<vector<int>>& seq, int target) {
        auto modPow = [&](int x, int k, int m) {
            int ret = 1 % m;
            for( ; k > 0; k >>= 1, x = x * x % m)
                if(k & 1)
                    ret = ret * x % m;
            return ret;
        };
        int n = seq.size();
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            auto &vec = seq[i];
            if(modPow(modPow(vec[0], vec[1], 10), vec[2], vec[3]) == target)
                ret.push_back(i);
        }
        return ret;
    }
};
