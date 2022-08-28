class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int upp = INT_MAX;
        stack<int> stk;
        for(int x: nums) {
            if(x > upp)
                return true;
            for( ; !stk.empty() && stk.top() >= x; stk.pop());
            stk.push(x);
            if(stk.size() > 1)
                upp = min(upp, x);
        }
        return false;
    }
};
