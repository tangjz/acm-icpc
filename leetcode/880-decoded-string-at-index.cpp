class Solution {
public:
    string decodeAtIndex(string s, int k) {
        typedef long long LL;
        int n = s.size();
        stack<pair<string, pair<int, LL> > > stk;
        stk.push({"", {1, 0LL}});
        for(int i = 0, j; stk.top().second.second < k; i = j) {
            for(j = i; j < n && islower(s[j]); ++j);
            string rep = s.substr(i, j - i);
            int c = 1;
            if(j < n)
                c = s[j++] - '0';
            stk.push({rep, {c, (stk.top().second.second + rep.size()) * c}});
        }
        while(stk.size() > 1) {
            pair<string, pair<int, LL> > cur = stk.top();
            stk.pop();
            int per = cur.second.second / cur.second.first;
            k = (k - 1) % per + 1;
            if(k > stk.top().second.second)
                return cur.first.substr(k - stk.top().second.second - 1, 1);
        }
        return "";
    }
};
