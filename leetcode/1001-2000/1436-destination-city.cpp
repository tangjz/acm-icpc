class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_set<string> Hash;
        for(auto &it : paths)
            Hash.insert(it[0]);
        for(auto &it : paths)
            if(Hash.find(it[1]) == Hash.end())
                return it[1];
        assert(0);
    }
};
