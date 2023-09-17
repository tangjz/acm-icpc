class Solution {
public:
    int maxProduct(vector<int>& nums) {
        typedef long long LL;
        LL ans = nums.front(), mx = 1, mn = 1;
        for(int x: nums) {
            mx *= x;
            mn *= x;
            if(mx < mn)
                swap(mx, mn);
            mx = max(mx, (LL)x);
            mn = max(min(mn, (LL)x), (LL)INT_MIN);
            ans = max(ans, mx);
        }
        return ans;
    }
};
