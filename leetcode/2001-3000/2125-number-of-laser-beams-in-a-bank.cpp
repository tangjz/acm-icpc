class Solution {
    int count(string_view s, char pat) {
        int cnt = 0;
        for(char ch: s)
            cnt += ch == pat;
        return cnt;
    }
public:
    int numberOfBeams(vector<string>& bank) {
        int ans = 0, las = 0;
        for(auto &it: bank) {
            int val = count(it, '1');
            if(!val)
                continue;
            ans += las * val;
            las = val;
        }
        return ans;
    }
};
