class NumArray {
    vector<int> psums;
public:
    NumArray(vector<int>& nums) {
        psums = {0};
        for(int x: nums)
            psums.push_back(psums.back() + x);
    }

    int sumRange(int left, int right) {
        return psums[right + 1] - psums[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
