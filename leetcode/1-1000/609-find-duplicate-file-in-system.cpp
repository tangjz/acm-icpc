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
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        map<string, vector<string> > mp;
        for(auto &it: paths) {
            vector<string_view> items = split(it, ' ');
            reverse(items.begin(), items.end());
            string prefix = (string)items.back();
            items.pop_back();
            while(!items.empty()) {
                string_view item = items.back();
                auto pos = item.find('(');
                string name = prefix + "/" + (string)item.substr(0, pos), cont = (string)item.substr(pos + 1, item.size() - pos - 2);
                mp[cont].push_back(name);
                items.pop_back();
            }
        }
        vector<vector<string> > ret;
        for(auto &it: mp)
            if(it.second.size() > 1)
                ret.push_back(it.second);
        return ret;
    }
};
