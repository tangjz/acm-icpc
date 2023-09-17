class MapSum {
    struct TrieNode {
        int sum, val;
        map<char, TrieNode *> childs;
        TrieNode() : sum(0), val(0), childs(map<char, TrieNode *>()) {}
    } *root;
public:
    MapSum() {
        root = new TrieNode();
    }

    void insert(string key, int val) {
        TrieNode *cur = root;
        cur -> sum += val;
        for(char ch: key) {
            auto &childs = cur -> childs;
            auto it = childs.find(ch);
            if(it == childs.end()) {
                TrieNode *adt = new TrieNode();
                childs.insert(make_pair(ch, adt));
                cur = adt;
            } else {
                cur = it -> second;
            }
            cur -> sum += val;
        }
        int dt = cur -> val;
        cur -> val = val;
        if(!dt)
            return;
        cur = root;
        cur -> sum -= dt;
        for(char ch: key) {
            auto &childs = cur -> childs;
            auto it = childs.find(ch);
            cur = it -> second;
            cur -> sum -= dt;
        }
    }

    int sum(string prefix) {
        TrieNode *cur = root;
        for(char ch: prefix) {
            auto &childs = cur -> childs;
            auto it = childs.find(ch);
            if(it == childs.end()) {
                return 0;
            }
            cur = it -> second;
        }
        return cur -> sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
