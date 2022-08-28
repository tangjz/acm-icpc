class Solution {
public:
    string entityParser(string text) {
        const char *trans[6][2] = {
            {"&quot;", "\""},
            {"&apos;", "\'"},
            {"&gt;", ">"},
            {"&lt;", "<"},
            {"&frasl;", "/"},
            {"&amp;", "&"}
        };
        for(int i = 0; i < 6; ++i) {
            const char *s = trans[i][0], *t = trans[i][1];
            int slen = strlen(s), tlen = strlen(t);
            for(auto pos = text.find(s); pos != string::npos; pos = text.find(s, pos + tlen))
                text.replace(pos, slen, t);
        }
        return text;
    }
};
