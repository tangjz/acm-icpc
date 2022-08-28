class Solution {
public:
    bool check(vector<int>& nums) {
        int n = (int)nums.size();
        for(int i = 0; i < n; ++i) {
            int las = nums[i];
            bool valid = 1;
            for(int j = 1; valid && j < n; ++j) {
                int cur = nums[(i + j) % n];
                valid &= las <= cur;
                las = cur;
            }
            if(valid)
                return 1;
        }
        return 0;
    }
};
