class Solution {
public:
    string evaluate(string_view s, vector<vector<string>>& knowledge) {
        string t;
        unordered_map<string, string> mp;
        for(auto &it: knowledge)
            mp.insert({it[0], it[1]});
        while(!s.empty()) {
            auto L = s.find('(');
            if(L == string::npos) {
                t += (string)s;
                s = s.substr(s.size());
                continue;
            }
            t += (string)s.substr(0, L);
            auto R = s.find(')', L);
            string key = (string)s.substr(L + 1, R - L - 1);
            auto it = mp.find(key);
            if(it == mp.end()) {
                t.push_back('?');
            } else {
                t += it -> second;
            }
            s = s.substr(R + 1);
        }
        return t;
    }
};
