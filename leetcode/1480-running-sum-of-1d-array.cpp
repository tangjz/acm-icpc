class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> ret;
        int sum = 0;
        for(int x : nums) {
            sum += x;
            ret.push_back(sum);
        }
        return ret;
    }
};
