class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<vector<int>, vector<string> > Hash;
        for(string &buf : strs) {
            vector<int> ctr = vector<int>(26);
            for(char ch : buf)
                ++ctr[(int)(ch - 'a')];
            Hash[ctr].push_back(buf);
        }
        vector<vector<string> > ret;
        ret.reserve(Hash.size());
        for(auto &it : Hash)
            ret.push_back(move(it.second));
        return ret;
    }
};
