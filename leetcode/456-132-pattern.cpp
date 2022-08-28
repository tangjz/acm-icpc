class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size(), upp = INT_MIN;
        stack<int> stk;
        for(int i = n - 1; i >= 0; --i) {
            int x = nums[i];
            if(x < upp)
                return 1;
            while(!stk.empty() && stk.top() < x) {
                upp = max(upp, stk.top());
                stk.pop();
            }
            stk.push(x);
        }
        return 0;
    }
};
