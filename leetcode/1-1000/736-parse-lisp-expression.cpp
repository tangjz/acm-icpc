class Solution {
    int dfs(int dep, int L, int R, string const &s, unordered_map<int, int> &pR, unordered_map<string, vector<int> > &var) {
        // integer
        if(s[L] == '-' || isdigit(s[L]))
            return stoi(s.substr(L, R - L + 1));
        // assigned variable
        if(s[L] != '(') {
            auto it = var.find(s.substr(L, R - L + 1));
            assert(it != var.end());
            return (it -> second).back();
        }
        // nested expressions
        if(s[L + 1] == 'a') {
            int u = pR[L], v = pR[u];
            assert(pR[v] == R);
            return dfs(dep + 1, u + 1, v - 1, s, pR, var) + dfs(dep + 1, v + 1, R - 1, s, pR, var);
        }
        if(s[L + 1] == 'm') {
            int u = pR[L], v = pR[u];
            assert(pR[v] == R);
            return dfs(dep + 1, u + 1, v - 1, s, pR, var) * dfs(dep + 1, v + 1, R - 1, s, pR, var);
        }
        bool assigned = 0;
        int ret;
        stack<string> stk;
        for(int u = pR[L], v = pR[u]; ; u = pR[v], v = pR[u]) {
            if(v == R) {
                assigned = 1;
                ret = dfs(dep + 1, u + 1, v - 1, s, pR, var);
                break;
            }
            string key = s.substr(u + 1, v - u - 1);
            int val = dfs(dep + 1, v + 1, pR[v] - 1, s, pR, var);
            var[key].push_back(val);
            stk.push(key);
        }
        assert(assigned);
        while(!stk.empty()) {
            string const &key = stk.top();
            var[key].pop_back();
            if(var[key].empty())
                var.erase(key);
            stk.pop();
        }
        return ret;
    }
public:
    int evaluate(string expression) {
        int n = expression.size();
        unordered_map<int, int> pR;
        stack<int> stk;
        for(int i = 0; i < n; ++i)
            if(expression[i] == '(') {
                stk.push(i);
            } else if(expression[i] == ')') {
                pR[stk.top()] = i;
                stk.pop();
            } else if(expression[i] == ' ') {
                pR[stk.top()] = i;
                stk.pop();
                stk.push(i);
            }
        unordered_map<string, vector<int> > var;
        return dfs(0, 0, n - 1, expression, pR, var);
    }
};
