class Solution {
    void replace(string &text, char pat, string const &rep) {
        int n = text.size(), cnt = 0;
        for(int i = 0; i < n; ++i)
            cnt += text[i] == pat;
        int m = n + cnt * (rep.size() - 1);
        text.resize(m);
        for(int i = n - 1; i >= 0; --i)
            if(text[i] == pat) {
                for(int j = rep.size() - 1; j >= 0; --j)
                    text[--m] = rep[j];
            } else {
                text[--m] = text[i];
            }
    }
public:
    string defangIPaddr(string address) {
        replace(address, '.', "[.]");
        return address;
    }
};
