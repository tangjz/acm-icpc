class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, L = 0, R = (int)height.size() - 1;
        while(L <= R) {
            int com = min(height[L], height[R]);
            for( ; L <= R && height[L] <= com; ++L)
                ans += com - height[L];
            for( ; L <= R && height[R] <= com; --R)
                ans += com - height[R];
        }
        return ans;
    }
};
