class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        for(int x: nums) {
            int y = x < 0 ? -1 - x : x;
            if(nums[y] < 0)
                return y;
            nums[y] = -1 - nums[y];
        }
        return -1;
    }
};
