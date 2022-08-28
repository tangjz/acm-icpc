class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        int n = nums.size();
        vector<int> pos;
        for(int i = 1; i < n; ++i)
            if(nums[i - 1] >= nums[i]) {
                pos.push_back(i);
                if(pos.size() > 1)
                    return false;
            }
        if(pos.empty())
            return true;
        int x = pos.front();
        if(nums[x - 1] < (x + 1 < n ? nums[x + 1] : INT_MAX))
            return true;
        if((x - 2 >= 0 ? nums[x - 2] : INT_MIN) < nums[x])
            return true;
        return false;
    }
};
