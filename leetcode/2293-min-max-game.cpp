class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        while(nums.size() > 1) {
            int n = nums.size();
            for(int i = 0; i + i + 1 < n; ++i) {
                int lft = nums[i + i], rht = nums[i + i + 1];
                nums[i] = i & 1 ? max(lft, rht) : min(lft, rht);
            }
            nums.resize(n / 2);
        }
        return nums[0];
    }
};
