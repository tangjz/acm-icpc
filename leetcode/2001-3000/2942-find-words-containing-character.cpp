class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        int n = words.size();
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            for(char ch: words[i])
                if(x == ch) {
                    ret.push_back(i);
                    break;
                }
        return ret;
    }
};
