class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        typedef long long LL;
        stack<LL> stk;
        for(auto &it: tokens) {
            if(it.back() >= '0' && it.back() <= '9') {
                stk.push(stoi(it));
                continue;
            }
            LL v = stk.top();
            stk.pop();
            LL u = stk.top();
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
