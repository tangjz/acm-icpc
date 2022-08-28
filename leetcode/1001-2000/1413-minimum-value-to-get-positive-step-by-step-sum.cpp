class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int ans = 0, sum = 0;
        for(int x : nums) {
            sum += x;
            ans = min(ans, sum);
        }
        return -ans + 1;
    }
};
