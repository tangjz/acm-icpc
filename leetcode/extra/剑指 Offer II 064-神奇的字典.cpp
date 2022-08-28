class MagicDictionary {
    unordered_set<string> sp;
    unordered_map<string, int> ctr;
public:
    MagicDictionary() {
        
    }
    
    void buildDict(vector<string> dictionary) {
        sp.clear();
        ctr.clear();
        for(auto &buf: dictionary) {
            sp.insert(buf);
            for(char &ch: buf) {
                char tmp = '*';
                swap(ch, tmp);
                ++ctr[buf];
                swap(ch, tmp);
            }
        }
    }
    
    bool search(string searchWord) {
        int low = sp.count(searchWord);
        for(char &ch: searchWord) {
            char tmp = '*';
            swap(ch, tmp);
            auto it = ctr.find(searchWord);
            if(it != ctr.end() && it -> second > low)
                return 1;
            swap(ch, tmp);
        }
        return 0;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
