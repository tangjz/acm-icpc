class Solution {
public:
    long long subsequenceSumOr(vector<int>& nums) {
        typedef long long LL;
        LL ans = 0, sum = 0;
        for(int x: nums) {
            ans |= x;
            ans |= (sum += x);
        }
        return ans;
    }
};
