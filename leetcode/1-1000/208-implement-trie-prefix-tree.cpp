class Trie {
    static const int maxd = 26;
    struct Node {
        bool end;
        Node *nxt[maxd];
    } *rt;
public:
    /** Initialize your data structure here. */
    Trie() {
        rt = new Node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node *cur = rt;
        for(char ch: word) {
            int o = ch - 'a';
            if(cur -> nxt[o] == nullptr)
                cur -> nxt[o] = new Node();
            cur = cur -> nxt[o];
        }
        cur -> end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node *cur = rt;
        for(char ch: word) {
            int o = ch - 'a';
            if(cur -> nxt[o] == nullptr)
                return false;
            cur = cur -> nxt[o];
        }
        return cur -> end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node *cur = rt;
        for(char ch: prefix) {
            int o = ch - 'a';
            if(cur -> nxt[o] == nullptr)
                return false;
            cur = cur -> nxt[o];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
