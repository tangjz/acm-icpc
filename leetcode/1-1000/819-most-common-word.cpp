class Solution {
    vector<string_view> split(string_view s, char sep = '.') {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0; i < n; ++i) {
            int j = i;
            for( ; i < n && s[i] != sep; ++i);
            ret.push_back(s.substr(j, i - j));
        }
        if(!s.empty() && s.back() == sep)
            ret.push_back(s.substr(s.size()));
        return move(ret);
    }
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_set<char> skp = {'!', '?', ',', ';', '.', '\'', '"'};
        unordered_set<string> ban(banned.begin(), banned.end());
        for(char &ch: paragraph)
            if(skp.count(ch)) {
                ch = ' ';
            } else {
                ch = tolower(ch);
            }
        int occ = 0;
        vector<string> ret;
        unordered_map<string, int> ctr;
        vector<string_view> items = split(paragraph, ' ');
        for(auto &item: items) {
            if(item.empty() || ban.count((string)item))
                continue;
            int cur = ++ctr[(string)item];
            if(occ < cur) {
                ret.clear();
                occ = cur;
            }
            if(occ == cur)
                ret.push_back((string)item);
        }
        return ret[0];
    }
};
