class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        vector<int> ctr(right + 1);
        for(auto &it: ranges)
            for(int i = it[0]; i <= right && i <= it[1]; ++i)
                ++ctr[i];
        for(int i = left; i <= right; ++i)
            if(!ctr[i])
                return false;
        return true;
    }
};
