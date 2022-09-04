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
    string join(vector<string_view> seq, char sep = ' ') {
        int len = 0;
        for(auto &it: seq)
            len += (len > 0) + it.size();
        string ret;
        ret.reserve(len);
        for(auto &it: seq) {
            if(!ret.empty())
                ret.push_back(sep);
            ret += it;
        }
        return ret;
    }
public:
    string simplifyPath(string_view path) {
        int tot = 0;
        vector<string_view> items = split(path, '/');
        for(auto &item: items) {
            if(item.empty() || item == ".")
                continue;
            if(item == "..") {
                tot > 0 && (--tot);
                continue;
            }
            items[tot++] = move(item);
        }
        items.resize(tot);
        return "/" + join(items, '/');
    }
};
