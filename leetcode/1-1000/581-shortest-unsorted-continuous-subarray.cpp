class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int L = 0, R = nums.size() - 1;
        vector<int> vec = nums;
        sort(vec.begin(), vec.end());
        for( ; L <= R && nums[L] == vec[L]; ++L);
        for( ; L <= R && nums[R] == vec[R]; --R);
        return R - L + 1;
    }
};
