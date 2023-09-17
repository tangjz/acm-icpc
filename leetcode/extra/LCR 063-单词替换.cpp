class Solution {
    struct TrieNode {
        bool hasEnd;
        map<char, TrieNode *> childs;
        TrieNode() : hasEnd(0), childs(map<char, TrieNode *>()) {}
    } ;
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        TrieNode *root = new TrieNode();
        for(string &word: dictionary) {
            TrieNode *cur = root;
            for(char ch: word) {
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
        string ret = "", tmp = "";
        TrieNode *cur = root;
        for(char ch: sentence) {
            if(ch == ' ' || cur == nullptr || !(cur -> hasEnd))
                tmp.push_back(ch);
            if(ch == ' ') {
                ret += tmp;
                tmp = "";
                cur = root;
                continue;
            }
            if(cur != nullptr && !(cur -> hasEnd)) {
                auto &childs = cur -> childs;
                auto it = childs.find(ch);
                if(it != childs.end()) {
                    cur = it -> second;
                } else {
                    cur = nullptr;
                }
            }
        }
        ret += tmp;
        return ret;
    }
};
