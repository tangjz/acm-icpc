class Solution {
public:
    string decodeString(string s) {
        int n = s.size();
        string t = "";
        for(int i = 0, j; i < n; i = j) {
            j = i + 1;
            if(s[i] >= 'a' && s[i] <= 'z') {
                t += s[i];
                continue;
            }
            int rep = s[i] - '0';
            for( ; j < n && s[j] >= '0' && s[j] <= '9'; ++j)
                rep = rep * 10 + (s[j] - '0');
            string p = "";
            int c = 0;
            assert(s[j] == '[');
            for(++j, ++c; j < n && c > 0; ++j) {
                p += s[j];
                if(s[j] == '[') {
                    ++c;
                } else if(s[j] == ']') {
                    --c;
                }
            }
            assert(p.back() == ']');
            p.pop_back();
            // printf("p %s c %d\n", p.c_str(), c);
            assert(c == 0);
            p = decodeString(p);
            while(rep--)
                t += p;
        }
        return t;
    }
};
