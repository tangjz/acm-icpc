class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        const int maxd = 26;
        vector<int> ctr(maxd, 0);
        for(char ch : ransomNote)
            --ctr[(int)(ch - 'a')];
        for(char ch : magazine)
            ++ctr[(int)(ch - 'a')];
        return *min_element(ctr.begin(), ctr.end()) >= 0;
    }
};
