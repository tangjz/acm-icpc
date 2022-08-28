class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        int n = s.size();
        for(int i = 0; i < n; ++i) {
            if(s[i] >= '0' && s[i] <= '9')
                continue;
            string p = s.substr(0, i + 1);
            string q = p;
            q.back() = q.back() <= 'Z' ? q.back() - 'A' + 'a' : q.back() - 'a' + 'A';
            vector<string> tmp = letterCasePermutation(s.substr(i + 1));
            vector<string> adt;
            for(auto &it: tmp) {
                adt.push_back(p + it);
                it = q + it;
            }
            adt.insert(adt.end(), tmp.begin(), tmp.end());
            return adt;
        }
        return {s};
    }
};
