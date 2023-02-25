class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        int r = 0;
        vector<int> ans;
        for(char ch: word) {
            r = (10LL * r + (ch - '0')) % m;
            ans.push_back(!r);
        }
        return ans;
    }
};
