class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        unordered_set<string> vis;
        unordered_map<string, int> las;
        vector<string> ret;
        for(auto &it : names) {
            if(!vis.count(it)) {
                ret.push_back(it);
            } else {
                int &pos = las[it];
                for(++pos; vis.count(it + '(' + to_string(pos) + ')'); ++pos);
                ret.push_back(it + '(' + to_string(pos) + ')');
            }
            vis.insert(ret.back());
        }
        return ret;
    }
};
