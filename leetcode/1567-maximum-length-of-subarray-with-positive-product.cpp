class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int n = (int)nums.size();
        int ans = 0, pos = 0, las[2] = {-1, n}, sum = 0;
        for(int x : nums) {
            if(!x) {
                las[0] = pos;
                las[1] = n;
                sum = 0;
            } else {
                sum ^= x < 0;
                las[sum] = min(las[sum], pos);
                ans = max(ans, pos - las[sum]);
            }
            ++pos;
        }
        return ans;
    }
};
