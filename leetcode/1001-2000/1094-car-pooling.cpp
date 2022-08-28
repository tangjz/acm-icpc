class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        const int maxd = 1001;
        vector<int> ctr(maxd);
        for(auto &it: trips) {
            ctr[it[1]] += it[0];
            ctr[it[2]] -= it[0];
        }
        for(int i = 0; i < maxd; ++i) {
            ctr[i] += i ? ctr[i - 1] : 0;
            if(ctr[i] > capacity)
                return 0;
        }
        return 1;
    }
};
