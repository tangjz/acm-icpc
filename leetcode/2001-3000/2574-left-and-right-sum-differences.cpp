class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int lft = 0, rht = 0;
        vector<int> ans;
        for(int x: nums)
            rht += x;
        for(int x: nums) {
            rht -= x;
            ans.push_back(abs(lft - rht));
            lft += x;
        }
        return ans;
    }
};
