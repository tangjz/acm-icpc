class Solution {
public:
    long long maxStrength(vector<int>& nums) {
        typedef long long LL;
        LL low = nums.back(), upp = low;
        nums.pop_back();
        for(int x: nums) {
            LL p = min(min(low, (LL)x), min(low * x, upp * x));
            LL q = max(max(upp, (LL)x), max(low * x, upp * x));
            low = p;
            upp = q;
        }
        return upp;
    }
};
