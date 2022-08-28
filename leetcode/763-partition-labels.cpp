class Solution {
public:
    vector<int> partitionLabels(string S) {
        int len = 0;
        unordered_map<char, int> las;
        for(char ch : S)
            las[ch] = len++;
        int pos = 0, lft = 0, rht = 0;
        vector<int> ret;
        for(char ch : S) {
            rht = max(rht, las[ch]);
            if(pos == rht) {
                ret.push_back(rht - lft + 1);
                lft = rht + 1;
            }
            ++pos;
        }
        return ret;
    }
};
