class Solution {
    vector<string_view> split(string_view s, char sep = '.') {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0; i < n; ++i) {
            int j = i;
            for( ; i < n && s[i] != sep; ++i);
            ret.push_back(s.substr(j, i - j));
        }
        if(!s.empty() && s.back() == sep)
            ret.push_back(s.substr(s.size()));
        return move(ret);
    }
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> ctr(n);
        stack<int> stk;
        int las = 0;
        for(auto &row: logs) {
            vector<string_view> items = split(row, ':');
            int idx = stoi((string)items[0]), tim = stoi((string)items[2]);
            bool typ = items[1] == "end";
            tim += typ;
            if(!stk.empty())
                ctr[stk.top()] += tim - las;
            if(typ) {
                stk.pop();
            } else {
                stk.push(idx);
            }
            las = tim;
        }
        return ctr;
    }
};
