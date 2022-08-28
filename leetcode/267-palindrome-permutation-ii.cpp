class Solution {
public:
    vector<string> generatePalindromes(string s) {
        map<char, int> ctr;
        for(char ch: s)
            ++ctr[ch];
        vector<string> ret;
        char ch = '\0';
        string u = "";
        for(auto &it: ctr) {
            if(it.second & 1) {
                if(ch)
                    return ret;
                ch = it.first;
                --it.second;
            }
            u += string(it.second >> 1, it.first);
        }
        do {
            string v = u;
            if(ch)
                v.push_back(ch);
            reverse(v.begin(), v.end());
            ret.push_back(u + v);
        } while(next_permutation(u.begin(), u.end()));
        return ret;
    }
};
