class Solution {
public:
    int calculate(string s) {
        stack<pair<int, char> > vals;
        int val = 0;
        auto check = [&]() {
            if(!vals.empty()) {
                int pre;
                char op;
                tie(pre, op) = vals.top();
                if(op == '*' || op == '/') {
                    vals.pop();
                    val = op == '*' ? pre * val : pre / val;
                }
            }
        };
        for(char ch : s) {
            if(ch == ' ')
                continue;
            if(ch >= '0' && ch <= '9') {
                val = val * 10 + (ch - '0');
                continue;
            }
            check();
            vals.push(make_pair(val, ch));
            val = 0;
        }
        check();
        int ans = 0;
        while(!vals.empty()) {
            int pre;
            char op;
            tie(pre, op) = vals.top();
            vals.pop();
            ans += op == '+' ? val : -val;
            val = pre;
        }
        ans += val;
        return ans;
    }
};
