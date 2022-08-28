class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> stk;
        for(int x: asteroids)
            if(x > 0) {
                stk.push(x);
            } else {
                while(!stk.empty() && stk.top() > 0 && stk.top() < -x)
                    stk.pop();
                if(stk.empty() || stk.top() < 0) {
                    stk.push(x);
                } else if(stk.top() == -x) {
                    stk.pop();
                }
            }
        vector<int> ret;
        for( ; !stk.empty(); ret.push_back(stk.top()), stk.pop());
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
