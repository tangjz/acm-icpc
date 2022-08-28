class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        typedef long long LL;
        vector<LL> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        int pos = -1, ans = INT_MAX, n = nums.size();
        for(int i = 0; i < n; ++i) {
            int lft = psum[i + 1] / (i + 1);
            int rht = i + 1 < n ? (psum[n] - psum[i + 1]) / (n - (i + 1)) : 0;
            int tmp = abs(lft - rht);
            if(ans > tmp) {
                ans = tmp;
                pos = i;
            }
        }
        return pos;
    }
};
