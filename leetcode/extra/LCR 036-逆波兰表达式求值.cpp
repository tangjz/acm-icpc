class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for(auto &it: tokens) {
            if(it.back() >= '0' && it.back() <= '9') {
                stk.push(stoi(it));
                continue;
            }
            int v = stk.top();
            stk.pop();
            int u = stk.top();
            stk.pop();
            switch(it[0]) {
                case '+': {
                    stk.push(u + v);
                    break;
                }
                case '-': {
                    stk.push(u - v);
                    break;
                }
                case '*': {
                    stk.push(u * v);
                    break;
                }
                case '/': {
                    stk.push(u / v);
                    break;
                }
            }
        }
        return stk.top();
    }
};
