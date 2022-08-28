class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = n - 1; i >= 0; --i) {
            int j = n - i, L = i > 0 ? nums[i - 1] + 1 : 0, R = nums[i];
            if(L <= j && j <= R)
                return j;
        }
        return -1;
    }
};
