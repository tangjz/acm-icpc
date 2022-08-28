class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end(), [&](string const &u, string const &v) {
            int dt = (int)u.size() - (int)v.size();
            return dt < 0 || (!dt && u > v);
        });
        int n = words.size(), las = -1;
        unordered_set<string> sp;
        sp.insert("");
        for(int i = 0; i < n; ++i) {
            if(words[i].empty())
                continue;
            char ch = words[i].back();
            words[i].pop_back();
            bool has = sp.count(words[i]);
            words[i].push_back(ch);
            if(has) {
                sp.insert(words[i]);
                las = i;
            }
        }
        return las == -1 ? "" : words[las];
    }
};
