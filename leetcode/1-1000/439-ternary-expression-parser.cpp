class Solution {
public:
    string parseTernary(string expression) {
        stack<int> stk;
        stk.push(expression.back());
        expression.pop_back();
        while(!expression.empty()) {
            char ch = expression.back();
            expression.pop_back();
            if(ch == '?') {
                ch = expression.back();
                expression.pop_back();
                char lft = stk.top();
                stk.pop();
                char rht = stk.top();
                stk.pop();
                if(ch == 'F' || ch == '0') {
                    stk.push(rht);
                } else {
                    stk.push(lft);
                }
            } else {
                stk.push(expression.back());
                expression.pop_back();
            }
        }
        string ret = "";
        ret.push_back(stk.top());
        return ret;
    }
};
