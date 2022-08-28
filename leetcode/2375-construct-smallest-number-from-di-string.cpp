class Solution {
public:
    string smallestNumber(string pattern) {
        int n = pattern.size() + 1;
        string buf = "";
        for(int i = 0; i < n; ++i)
            buf.push_back('1' + i);
        do {
            bool ok = 1;
            for(int i = 1; ok && i < n; ++i)
                ok &= (buf[i - 1] < buf[i]) == (pattern[i - 1] == 'I');
            if(ok)
                return buf;
        } while(next_permutation(buf.begin(), buf.end()));
        return "";
    }
};
