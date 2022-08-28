class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = (int)nums.size();
        if(n <= 1)
            return;
        int k = (n + 1) >> 1;
        nth_element(nums.begin(), nums.begin() + k, nums.end());
        for(int i = k - 1; i > 0; --i)
            swap(nums[i], nums[i << 1]);
    }
};
