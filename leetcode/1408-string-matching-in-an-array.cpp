class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> ret;
        int n = (int)words.size();
        for(int i = 0; i < n; ++i) {
            int len0 = (int)words[i].length();
            for(int j = 0; j < n; ++j) {
                int len1 = (int)words[j].length();
                if(i == j || len0 > len1)
                    continue;
                bool chk = 0;
                for(int k = 0; k + len0 <= len1; ++k)
                    if(words[i] == words[j].substr(k, len0)) {
                        chk = 1;
                        break;
                    }
                if(chk) {
                    ret.push_back(words[i]);
                    break;
                }
            }
        }
        return ret;
    }
};
