class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> ret(n, 1);
        for(int i = 1; i < n; ++i)
            if(ratings[i] > ratings[i - 1])
                ret[i] = max(ret[i], ret[i - 1] + 1);
        for(int i = n - 2; i >= 0; --i)
            if(ratings[i] > ratings[i + 1])
                ret[i] = max(ret[i], ret[i + 1] + 1);
        return accumulate(ret.begin(), ret.end(), 0);
    }
};
