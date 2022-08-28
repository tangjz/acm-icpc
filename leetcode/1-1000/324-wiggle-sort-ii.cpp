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
        int sta = 0, val = nums[sta];
        for(int i = sta, j = sta; i < n; i += 2) {
            if(val < nums[i]) {
                val = nums[i];
                j = sta;
            }
            if(val != nums[i])
                continue;
            if(i != j)
                swap(nums[i], nums[j]);
            j += 2;
        }
        sta = n - 1 - (n & 1);
        val = nums[sta];
        for(int i = sta, j = sta; i > 0; i -= 2) {
            if(val > nums[i]) {
                val = nums[i];
                j = sta;
            }
            if(val != nums[i])
                continue;
            if(i != j)
                swap(nums[i], nums[j]);
            j -= 2;
        }
    }
};
