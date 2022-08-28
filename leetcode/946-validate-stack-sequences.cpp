class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;
        auto it = pushed.begin(), jt = popped.begin();
        while(jt != popped.end()) {
            while(it != pushed.end() && (stk.empty() || stk.top() != *jt))
                stk.push(*(it++));
            if(stk.empty() || stk.top() != *jt)
                return 0;
            stk.pop();
            ++jt;
        }
        return 1;
    }
};
