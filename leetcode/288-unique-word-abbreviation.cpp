class ValidWordAbbr {
    unordered_map<string, string> Hash;
    
    string abbr(string key) {
        if(key.size() <= 2)
            return key;
        string ret = "";
        ret.push_back(key.front());
        ret += to_string(key.size() - 2);
        ret.push_back(key.back());
        return ret;
    }
    
public:
    ValidWordAbbr(vector<string>& dictionary) {
        Hash.clear();
        for(auto &it: dictionary) {
            string pat = abbr(it);
            auto jt = Hash.find(pat);
            if(jt == Hash.end()) {
                Hash.insert({pat, it});
            } else if(jt -> second != it) {
                jt -> second = "";
            }
        }
    }
    
    bool isUnique(string word) {
        string pat = abbr(word);
        auto it = Hash.find(pat);
        return it == Hash.end() || it -> second == word;
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
