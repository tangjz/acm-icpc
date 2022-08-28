class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int ans = 0;
        stack<pair<int, pair<int, int> > > stk;
        for(int x: nums) {
            while(!stk.empty() && stk.top().first <= x) {
                int adt = max(stk.top().second.first, stk.top().second.second);
                stk.pop();
                if(!stk.empty())
                    stk.top().second.second = max(stk.top().second.second, adt);
            }
            int cur = stk.empty() ? 0 : stk.top().second.second + 1;
            // printf("%d: %d\n", x, cur);
            stk.push({x, {cur, 0}});
            ans = max(ans, cur);
        }
        return ans;
    }
};
