class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int p = nums[0], q = nums[p];
        while(p != q) { // find the length of the cycle
            p = nums[p];
            q = nums[nums[q]];
        }
        p = 0;
        while(p != q) { // find the entry of the cycle
            p = nums[p];
            q = nums[q];
        }
        return p;
    }
};
