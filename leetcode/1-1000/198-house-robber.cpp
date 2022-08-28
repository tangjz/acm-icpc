class Solution {
public:
    int rob(vector<int>& nums) {
        int f0 = 0, f1 = 0;
        for(int x : nums) {
            tie(f0, f1) = make_pair(f1, max(f0 + x, f1));
        }
        return max(f0, f1);
    }
};
