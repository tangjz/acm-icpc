class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int ans = 0, n = (int)heights.size();
        stack<int> stk;
        for(int i = 0; i < n; ++i) {
            while(!stk.empty() && heights[stk.top()] >= heights[i]) {
                int h = heights[stk.top()];
                stk.pop();
                int j = stk.empty() ? 0 : stk.top() + 1;
                ans = max(ans, h * (i - j));
            }
            stk.push(i);
        }
        return ans;
    }
};
