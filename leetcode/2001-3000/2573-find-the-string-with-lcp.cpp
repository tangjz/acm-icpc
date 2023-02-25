class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string s = string(n, ' ');
        char op = 'a';
        for(int i = 0; i < n; ++i) {
            if(s[i] != ' ')
                continue;
            if(op > 'z')
                return "";
            static queue<int> que;
            s[i] = op;
            que.push(i);
            while(!que.empty()) {
                int j = que.front();
                que.pop();
                for(int k = 0; k < n; ++k) {
                    if(!lcp[j][k])
                        continue;
                    if(s[k] == ' ') {
                        s[k] = op;
                        que.push(k);
                    } else if(s[k] != op) {
                        return "";
                    }
                }
            }
            ++op;
        }
        for(int i = n - 1; i >= 0; --i) {
            if(lcp[i][i] != n - i)
                return "";
            for(int j = i + 1; j < n; ++j) {
                if(lcp[i][j] != lcp[j][i])
                    return "";
                int tmp = s[i] == s[j] ? (j + 1 < n ? lcp[i + 1][j + 1] : 0) + 1 : 0;
                if(lcp[i][j] != tmp)
                    return "";
            }
        }
        return s;
    }
};
