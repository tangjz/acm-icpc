class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        int s = 0;
        vector<bool> ans;
        for(int x: nums) {
            s = (s << 1 | x) % 5;
            ans.push_back(!s);
        }
        return ans;
    }
};
