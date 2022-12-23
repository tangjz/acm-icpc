class Solution {
public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
        vector<int> ret;
        for(auto &it: queries) {
            int u = it[0], v = it[1], ans = 1;
            while(u != v) {
                if(u < v)
                    swap(u, v);
                u >>= 1;
                ++ans;
            }
            ret.push_back(ans);
        }
        return ret;
    }
};
