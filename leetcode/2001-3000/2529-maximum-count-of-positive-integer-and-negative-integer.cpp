class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int c[3] = {};
        for(int x: nums) {
            int sgn = (x > 0) - (x < 0);
            ++c[sgn + 1];
        }
        return max(c[0], c[2]);
    }
};
