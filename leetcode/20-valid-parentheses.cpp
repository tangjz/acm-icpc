class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for(char ch: s) {
            switch(ch) {
                case '(':
                    stk.push(')');
                    break;
                case '{':
                    stk.push('}');
                    break;
                case '[':
                    stk.push(']');
                    break;
                default:
                    if(stk.empty() || stk.top() != ch) {
                        return false;
                    }
                    stk.pop();
            }
        }
        return stk.empty();
    }
};
