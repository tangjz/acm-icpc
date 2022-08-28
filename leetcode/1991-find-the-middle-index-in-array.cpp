class Solution {
public:
    int findMiddleIndex(vector<int>& nums) {
        int n = nums.size();
        int lft = 0, rht = 0;
        for(int i = 0; i < n; ++i)
            rht += nums[i];
        for(int i = 0; i < n; ++i) {
            rht -= nums[i];
            if(lft == rht)
                return i;
            lft += nums[i];
        }
        return -1;
    }
};
