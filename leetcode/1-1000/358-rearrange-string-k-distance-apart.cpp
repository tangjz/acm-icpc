class Solution {
public:
    string rearrangeString(string s, int k) {
        const int maxd = 26;
        int n = s.size();
        string t = "";
        vector<int> c(maxd);
        for(char ch: s)
            ++c[(int)(ch - 'a')];
        priority_queue<pair<int, int> > que;
        for(int i = 0; i < maxd; ++i)
            if(c[i])
                que.push({c[i], i});
        for(int i = 0; i < n; ++i) {
            if(k && i - k >= 0) {
                int o = t[i - k] - 'a';
                if(c[o])
                    que.push({c[o], o});
            }
            if(que.empty())
                return "";
            int o = que.top().second;
            que.pop();
            t.push_back('a' + o);
            --c[o];
            if(!k && c[o])
                que.push({c[o], o});
        }
        return t;
    }
};
