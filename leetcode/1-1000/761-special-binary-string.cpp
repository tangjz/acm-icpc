class Solution {
public:
    string makeLargestSpecial(string S) {
        if(!S.length())
            return "";
        vector<string> part;
        for(int i = 0, j = 0; i < (int)S.length(); i = ++j) {
            for(int ctr = 0; j < (int)S.length(); ++j) {
                S[j] == '1' ? ++ctr : --ctr;
                if(ctr == 0) {
                    part.push_back('1' + makeLargestSpecial(S.substr(i + 1, j - i - 1)) + '0');
                    break;
                }
            }
        }
        sort(part.begin(), part.end(), [](string const &u, string const &v) {
            return u + v > v + u;
        });
        return accumulate(part.begin(), part.end(), string());
    }
};
