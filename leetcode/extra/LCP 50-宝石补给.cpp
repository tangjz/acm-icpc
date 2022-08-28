class Solution {
public:
    int giveGem(vector<int>& gem, vector<vector<int>>& operations) {
        for(auto &it: operations) {
            int x = it[0], y = it[1];
            int tp = gem[x] / 2;
            gem[x] -= tp;
            gem[y] += tp;
        }
        int upp = *max_element(gem.begin(), gem.end());
        int low = *min_element(gem.begin(), gem.end());
        return upp - low;
    }
};
