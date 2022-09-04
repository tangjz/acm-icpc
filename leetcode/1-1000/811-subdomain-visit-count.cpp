class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        map<string, int> ctr;
        for(auto &row: cpdomains) {
            auto pos = row.find(' ');
            int cnt = stoi(row.substr(0, pos));
            string_view name = ((string_view)row).substr(pos + 1);
            while(name != "") {
                ctr[(string)name] += cnt;
                auto pos = name.find('.');
                if(pos == string::npos)
                    break;
                name = name.substr(pos + 1);
            }
        }
        vector<string> ret;
        for(auto &it: ctr)
            ret.push_back(to_string(it.second) + " " + it.first);
        return ret;
    }
};
