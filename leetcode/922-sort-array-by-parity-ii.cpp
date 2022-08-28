class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size(), p = 0, q = 1;
        while(p < n && q < n) {
            for( ; p < n && !(nums[p] & 1); p += 2);
            for( ; q < n && (nums[q] & 1); q += 2);
            if(p < n) {
                assert(q < n);
                swap(nums[p], nums[q]);
            }
        }
        assert(p >= n && q >= n);
        return move(nums);
    }
};
