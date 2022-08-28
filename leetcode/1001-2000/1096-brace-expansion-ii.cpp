class Solution {
    unordered_set<string> dfs(int L, int R, string const &buf, vector<int> const &pR) {
        unordered_set<string> ret = {""};
        string pre = "";
        for(int i = L, j; i <= R; i = j) {
            j = i + 1;
            if(buf[i] != '{') {
                pre.push_back(buf[i]);
                continue;
            }
            unordered_set<string> cur = {};
            for(j = i; buf[j] != '}'; j = pR[j]) {
                unordered_set<string> nxt = dfs(j + 1, pR[j] - 1, buf, pR);
                if(cur.size() < nxt.size())
                    cur.swap(nxt);
                for(auto &it: nxt)
                    cur.insert(it);
            }
            unordered_set<string> nxt = {};
            for(auto &it: ret)
                for(auto &jt: cur)
                    nxt.insert(it + pre + jt);
            ret = move(nxt);
            pre = "";
            ++j;
        }
        if(pre != "") {
            unordered_set<string> nxt = {};
            for(auto &it: ret)
                nxt.insert(it + pre);
            ret = move(nxt);
        }
        return ret;
    }
public:
    vector<string> braceExpansionII(string expression) {
        int n = expression.size();
        vector<int> pR(n, -1);
        stack<int> stk;
        for(int i = 0; i < n; ++i) {
            char ch = expression[i];
            if(ch == '{') {
                stk.push(i);
            } else if(ch == '}') {
                pR[stk.top()] = i;
                stk.pop();
            } else if(ch == ',') {
                pR[stk.top()] = i;
                stk.pop();
                stk.push(i);
            }
        }
        unordered_set<string> ans = dfs(0, n - 1, expression, pR);
        vector<string> ret;
        ret.reserve(ans.size());
        for(auto &it: ans)
            ret.push_back(it);
        sort(ret.begin(), ret.end());
        return ret;
    }
};
