class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        int n = (int)colsum.size();
        vector<vector<int> > ret(2, vector<int>(n, 0));
        for(int i = 0; i < n; ++i) {
            int cur = colsum[i];
            if(cur == 1)
                continue;
            cur >>= 1;
            ret[0][i] = ret[1][i] = cur;
            upper -= cur;
            lower -= cur;
        }
        for(int i = 0; i < n; ++i) {
            if(colsum[i] != 1)
                continue;
            if(upper > 0) {
                ret[0][i] = 1;
                --upper;
            } else if(lower > 0) {
                ret[1][i] = 1;
                --lower;
            } else {
                return {};
            }
        }
        if(upper != 0 || lower != 0)
            return {};
        return ret;
    }
};
