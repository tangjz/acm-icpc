class Solution {
public:
    bool isUnique(string astr) {
        unordered_set<char> sp;
        for(char ch: astr)
            if(!sp.insert(ch).second)
                return 0;
        return 1;
    }
};
