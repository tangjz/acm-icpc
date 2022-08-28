class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), [&](string const &u, string const &v) {
            int dt = (int)u.size() - (int)v.size();
            return dt > 0 || (!dt && u < v);
        });
        for(auto &buf: dictionary) {
            int n = buf.size(), p = 0;
            if(!n)
                break;
            for(char ch: s)
                if(ch == buf[p] && (++p) == n)
                    return buf;
        }
        return "";
    }
};
