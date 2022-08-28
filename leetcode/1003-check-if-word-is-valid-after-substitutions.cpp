class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for(char ch: s)
            switch(ch) {
                case 'a': {
                    stk.push('a');
                    break;
                }
                case 'b': {
                    if(stk.empty() || stk.top() != 'a')
                        return 0;
                    stk.top() = 'b';
                    break;
                }
                case 'c': {
                    if(stk.empty() || stk.top() != 'b')
                        return 0;
                    stk.pop();
                    break;
                }
            }
        return stk.empty();
    }
};
