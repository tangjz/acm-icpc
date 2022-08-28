class Solution {
public:
    int lengthLongestPath(string_view input) {
        int ans = 0, tot = 0;
        stack<string_view> stk;
        for(int i = 0, j, n = input.size(); i < n; i = j + 1) {
            for(j = i; j < n && input[j] != '\n'; ++j);
            int lev = 0;
            for( ; i < j && input[i] == '\t'; ++i, ++lev);
            while(stk.size() > lev) {
                tot -= stk.top().size() + 1;
                stk.pop();
            }
            tot += j - i + 1;
            stk.push(input.substr(i, j - i));
            if(stk.top().find('.') != string::npos)
                ans = max(ans, tot - 1);
        }
        return ans;
    }
};
