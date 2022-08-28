class Solution {
public:
    string arrangeWords(string buf) {
        int len = (int)buf.length();
        vector<string> vec;
        for(int i = 0, j; i < len; i = j + 1) {
            for(j = i; j < len && buf[j] != ' '; ++j);
            vec.push_back(buf.substr(i, j - i));
        }
        char ch = vec[0][0];
        vec[0][0] = ch - 'A' + 'a';
        int n = (int)vec.size();
        vector<int> ord;
        for(int i = 0; i < n; ++i)
            ord.push_back(i);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            int diff = (int)vec[u].length() - (int)vec[v].length();
            return diff < 0 || (!diff && u < v);
        });
        string ret = "";
        for(int i = 0; i < n; ++i) {
            if(i > 0)
                ret += ' ';
            ret += vec[ord[i]];
        }
        ret[0] = ret[0] - 'a' + 'A';
        return ret;
    }
};
