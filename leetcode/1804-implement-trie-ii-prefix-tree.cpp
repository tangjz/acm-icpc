class Trie {
    static const int maxd = 26;
    struct Node {
        int cnt, sub;
        Node *nxt[maxd];
    } *rt;
public:
    Trie() {
        rt = new Node();
    }
    
    void insert(string word) {
        Node *cur = rt;
        for(char ch: word) {
            int o = ch - 'a';
            ++(cur -> sub);
            if(cur -> nxt[o] == nullptr)
                cur -> nxt[o] = new Node();
            cur = cur -> nxt[o];
        }
        ++(cur -> sub);
        ++(cur -> cnt);
    }
    
    int countWordsEqualTo(string word) {
        Node *cur = rt;
        for(char ch: word) {
            int o = ch - 'a';
            if(cur -> nxt[o] == nullptr)
                return 0;
            cur = cur -> nxt[o];
        }
        return cur -> cnt;
    }
    
    int countWordsStartingWith(string prefix) {
        Node *cur = rt;
        for(char ch: prefix) {
            int o = ch - 'a';
            if(cur -> nxt[o] == nullptr)
                return 0;
            cur = cur -> nxt[o];
        }
        return cur -> sub;
    }
    
    void erase(string word) {
        Node *cur = rt;
        for(char ch: word) {
            int o = ch - 'a';
            --(cur -> sub);
            assert(cur -> nxt[o] != nullptr);
            cur = cur -> nxt[o];
        }
        --(cur -> sub);
        --(cur -> cnt);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */
