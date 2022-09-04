class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int ans = 0;
        string cur = word;
        while(sequence.find(cur) != string::npos) {
            ++ans;
            cur += word;
        }
        return ans;
    }
};
