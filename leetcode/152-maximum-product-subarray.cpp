class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = nums.front(), mx = 1, mn = 1;
        for(int x : nums) {
            mx *= x;
            mn *= x;
            if(mx < mn)
                swap(mx, mn);
            mx = max(mx, x);
            mn = min(mn, x);
            ans = max(ans, mx);
        }
        return ans;
    }
};
