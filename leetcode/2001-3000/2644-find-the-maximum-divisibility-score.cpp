class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {
        pair<int, int> ans = {-1, -1};
        for(int x: divisors) {
            int c = 0;
            for(int y: nums)
                c += y % x == 0;
            ans = max(ans, make_pair(c, -x));
        }
        return -ans.second;
    }
};
