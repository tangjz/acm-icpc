class Solution {
public:
    int closetTarget(vector<string>& words, string t, int id) {
        int n = words.size(), ans = INT_MAX;
        for(int i = 0; i < n; ++i) {
            if(words[i] != t)
                continue;
            int tp = abs(i - id);
            ans = min(ans, min(tp, n - tp));
        }
        return ans < INT_MAX ? ans : -1;
    }
};
