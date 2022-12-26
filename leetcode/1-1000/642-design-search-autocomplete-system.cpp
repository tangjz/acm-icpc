class AutocompleteSystem {
    static const int maxd = 3;
    struct TrieNode {
        int val;
        vector<pair<int, string> > cand;
        map<char, TrieNode *> childs;
        TrieNode() : val(0), cand(), childs(map<char, TrieNode *>()) {}
    } *root, *cur;

    string buf;

    void insert(string key, int val = 1) {
        TrieNode *cur = root;
        auto extend = [&]() {
            int sz = cur -> cand.size();
            pair<int, string> state = {-val, key};
            for(int i = 0; i < sz; ++i) {
                if(cur -> cand[i].second == key) {
                    cur -> cand[i] = state;
                    return;
                }
                if(state < cur -> cand[i])
                    swap(state, cur -> cand[i]);
            }
            if(sz < maxd)
                cur -> cand.push_back(state);
        };
        extend();
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
            extend();
        }
        cur -> val = val;
    }


public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new TrieNode();
        int n = times.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return times[u] > times[v];
        });
        for(int i: ord)
            insert(sentences[i], times[i]);
        cur = root;
        buf = "";
    }

    vector<string> input(char ch) {
        vector<string> ret;
        if(ch == '#') {
            int val = 1 + (cur != nullptr ? cur -> val : 0);
            insert(buf, val);
            cur = root;
            buf = "";
            return ret;
        }
        buf.push_back(ch);
        if(cur != nullptr) {
            auto &childs = cur -> childs;
            auto it = childs.find(ch);
            if(it == childs.end()) {
                cur = nullptr;
            } else {
                cur = it -> second;
            }
        }
        if(cur != nullptr)
            for(auto &it: cur -> cand)
                ret.push_back(it.second);
        return ret;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
