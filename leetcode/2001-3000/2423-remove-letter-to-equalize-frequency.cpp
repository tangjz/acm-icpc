class Solution {
public:
    bool equalFrequency(string word) {
        unordered_map<char, int> ctr;
        vector<int> freq;
        for(char ch: word)
            ++ctr[ch];
        for(auto &it: ctr) {
            if(freq.size() <= it.second)
                freq.resize(it.second + 1);
            ++freq[it.second];
        }
        int n = word.size(), upp = freq.size() - 1;
        return upp == 1 || upp * freq[upp] + 1 == n || (freq[upp] == 1 && (upp - 1) * (freq[upp - 1] + 1) + 1 == n);
    }
};
