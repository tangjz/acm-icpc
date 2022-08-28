class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int cnt = 0, ans = 0;
        for(int x: nums) {
            if(!x) {
                cnt = 0;
            } else {
                ans = max(ans, ++cnt);
            }
        }
        return ans;
    }
};
