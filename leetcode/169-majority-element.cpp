class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans = 0, c = 0;
        for(int x: nums)
            if(!c) {
                ans = x;
                ++c;
            } else {
                x == ans ? ++c : --c;
            }
        return ans;
    }
};
