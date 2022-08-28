class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end(), [&](auto const &u, auto const &v) {
            int dt = (int)u.size() - (int)v.size();
            return dt < 0 || (!dt && u > v);
        });
        string las = "";
        unordered_set<string> cand = {""};
        for(auto &it: words) {
            char ch = it.back();
            it.pop_back();
            if(!cand.count(it))
                continue;
            it.push_back(ch);
            cand.insert(it);
            las = move(it);
        }
        return las;
    }
};
