class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        typedef long long LL;
        sort(nums.begin(), nums.end());
        vector<LL> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        vector<int> ans;
        for(int x: queries) {
            int y = upper_bound(psum.begin(), psum.end(), x) - psum.begin() - 1;
            ans.push_back(y);
        }
        return ans;
    }
};
