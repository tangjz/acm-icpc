class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ret;
        for(int x : nums) {
            int p = abs(x), &y = nums[p - 1];
            if(y < 0) {
                ret.push_back(p);
            } else {
                y = -y;
            }
        }
        return ret;
    }
};
