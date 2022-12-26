class WordDictionary {
    struct TrieNode {
        bool hasEnd;
        map<char, TrieNode *> childs;
        TrieNode() : hasEnd(0), childs(map<char, TrieNode *>()) {}
    } *root;

    bool dfs(string &word, int pos, TrieNode *rt) {
        if(pos == (int)word.size())
            return rt -> hasEnd;
        if(word[pos] == '.') {
            for(auto &it : rt -> childs)
                if(dfs(word, pos + 1, it.second))
                    return 1;
            return 0;
        }
        auto it = (rt -> childs).find(word[pos]);
        return it != (rt -> childs).end() && dfs(word, pos + 1, it -> second);
    }
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *cur = root;
        for(char ch : word) {
            auto &childs = cur -> childs;
            auto it = childs.find(ch);
            if(it == childs.end()) {
                TrieNode *adt = new TrieNode();
                childs.insert(make_pair(ch, adt));
                cur = adt;
            } else {
                cur = it -> second;
            }
        }
        cur -> hasEnd = 1;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return dfs(word, 0, root);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

static auto fastio = [](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return nullptr;
}();
