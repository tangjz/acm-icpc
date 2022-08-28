class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        int n = words.size();
        unordered_map<char, int> f, g;
        for(char ch: licensePlate) {
            if(!isalpha(ch))
                continue;
            ++f[(char)tolower(ch)];
        }
        int ans = -1;
        for(int i = 0; i < n; ++i) {
            int rem = f.size();
            g.clear();
            for(char ch: words[i])
                if(f.count(ch))
                    rem -= f[ch] == (++g[ch]);
            if(!rem && (ans == -1 || words[ans].size() > words[i].size()))
                ans = i;
        }
        return words[ans];
    }
};
