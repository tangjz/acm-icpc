class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        const int maxd = 26;
        unordered_map<string, vector<string> > Hash;
        for(auto &it: strings) {
            int dt = maxd - (it[0] - 'a');
            string buf = "";
            for(char ch: it)
                buf.push_back('a' + ((ch - 'a') + dt) % maxd);
            Hash[buf].push_back(move(it));
        }
        vector<vector<string> > ret;
        for(auto &it: Hash)
            ret.push_back(move(it.second));
        return ret;
    }
};
