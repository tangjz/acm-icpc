class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> ret;
        if(n & 1) {
            ret.push_back(0);
            --n;
        }
        for(int i = 0; i + i < n; ++i) {
            ret.push_back(i + 1);
            ret.push_back(-ret.back());
        }
        return ret;
    }
};
