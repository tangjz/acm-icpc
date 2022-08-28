class Solution {
public:
    int maxDepth(string s) {
        int ans = 0, cnt = 0;
        for(char ch: s) {
            if(ch == '(') {
                ++cnt;
                ans = max(ans, cnt);
            } else if(ch == ')') {
                --cnt;
            }
        }
        return ans;
    }
};
