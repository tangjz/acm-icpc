class Solution {
public:
    int maximumValue(vector<string>& strs) {
        int ans = 0;
        for(auto &s: strs) {
            bool bad = 0;
            int val = 0;
            for(char ch: s) {
                if(!isdigit(ch)) {
                    bad = 1;
                    break;
                }
                val = val * 10 + (ch - '0');
            }
            if(bad)
                val = s.size();
            ans = max(ans, val);
        }
        return ans;
    }
};
