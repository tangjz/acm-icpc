/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        const int maxt = 30, maxl = 6;
        int n = (int)wordlist.size();
        vector<int> ban(n, 0);
        vector<vector<int> > same(n, vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                for(int k = 0; k < maxl; ++k)
                    if(wordlist[i][k] == wordlist[j][k])
                        ++same[i][j];
        for(int t = 0; t < maxt; ++t) {
            int best = n + 1, pos = -1;
            for(int i = 0; i < n; ++i) {
                if(ban[i])
                    continue;
                int mx = 0;
                vector<int> ctr(maxl + 1, 0);
                for(int j = 0; j < n; ++j)
                    if(!ban[j])
                        mx = max(mx, ++ctr[same[i][j]]);
                if(best > mx) {
                    best = mx;
                    pos = i;
                }
            }
            int match = master.guess(wordlist[pos]);
            if(match == maxl)
                break;
            for(int i = 0; i < n; ++i)
                if(!ban[i] && same[pos][i] != match)
                    ban[i] = 1;
        }
    }
};
