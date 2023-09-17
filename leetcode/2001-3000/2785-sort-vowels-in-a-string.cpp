class Solution {
public:
    string sortVowels(string s) {
        static const char *pat = "aeiouAEIOU";
        int n = s.size();
        string t = "";
        for(int i = 0; i < n; ++i)
            for(int j = 0; pat[j]; ++j)
                if(s[i] == pat[j]) {
                    s[i] = '\0';
                    t.push_back(pat[j]);
                }
        sort(t.begin(), t.end());
        for(int i = n - 1; i >= 0; --i)
            if(s[i] == '\0') {
                s[i] = t.back();
                t.pop_back();
            }
        return s;
    }
};
