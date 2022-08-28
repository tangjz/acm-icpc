class Solution {
public:
    int maxArea(vector<int>& height) {
        int ans = 0;
        for(int L = 0, R = (int)height.size() - 1; L < R; )
            ans = max(ans, (R - L) * (height[L] < height[R] ? height[L++] : height[R--]));
        return ans;
    }
};
