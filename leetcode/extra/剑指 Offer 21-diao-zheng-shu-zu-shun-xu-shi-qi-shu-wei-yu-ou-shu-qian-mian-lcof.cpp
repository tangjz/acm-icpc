class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int L = 0, R = nums.size() - 1;
        while(L <= R) {
            if(nums[L] & 1) {
                ++L;
            } else {
                swap(nums[L], nums[R]);
                --R;
            }
        }
        return move(nums);
    }
};
