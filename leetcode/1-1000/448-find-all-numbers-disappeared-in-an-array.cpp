class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for(int x: nums) {
            int y = abs(x) - 1;
            if(nums[y] > 0)
                nums[y] = -nums[y];
        }
        vector<int> ret;
        for(int i = 0; i < (int)nums.size(); ++i)
            if(nums[i] > 0)
                ret.push_back(i + 1);
        return ret;
    }
};
