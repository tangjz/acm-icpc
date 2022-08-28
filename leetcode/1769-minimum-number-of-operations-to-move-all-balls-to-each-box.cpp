class Solution {
public:
    vector<int> minOperations(string s) {
        int n = (int)s.length();
        pair<int, int> rht = {0, 0}, lft = rht;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '1') {
                ++rht.first;
                rht.second += i;
            }
        }
        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            if(s[i] == '1') {
                --rht.first;
                ++lft.first;
                rht.second -= i;
                lft.second += i;
            }
            ans[i] = i * (lft.first - rht.first) + (rht.second - lft.second);
        }
        return ans;
    }
};
