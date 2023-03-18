class Solution {
public:
    int maxScore(vector<int>& nums) {
        typedef long long LL;
        int ans = 0;
        LL cur = 0;
        sort(nums.begin(), nums.end(), greater<int>());
        for(int x: nums) {
            cur += x;
            ans += cur > 0;
        }
        return ans;
    }
};
