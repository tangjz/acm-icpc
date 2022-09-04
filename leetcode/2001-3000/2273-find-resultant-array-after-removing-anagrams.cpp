class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> ret;
        string las, cur;
        for(auto &word: words) {
            cur = word;
            sort(cur.begin(), cur.end());
            if(las != cur) {
                ret.push_back(word);
                las = cur;
            }
        }
        return ret;
    }
};
