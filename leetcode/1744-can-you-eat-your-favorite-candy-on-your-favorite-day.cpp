class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        typedef long long LL;
        int n = (int)candiesCount.size();
        vector<LL> psum = {0LL};
        for(int x: candiesCount)
            psum.push_back(psum.back() + x);
        vector<bool> ans;
        for(auto &it: queries) {
            LL pL = psum[it[0]], pR = psum[it[0] + 1];
            LL low = it[1] + 1, upp = low * it[2];
            ans.push_back(pR >= low && pL < upp);
        }
        return ans;
    }
};
