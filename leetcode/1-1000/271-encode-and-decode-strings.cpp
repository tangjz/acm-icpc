class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string ret = "";
        for(auto &it: strs) {
            for(char ch: it) {
                int lo = ch & 15, hi = (ch >> 4) & 15;
                ret.push_back((char)(hi << 1 | 1));
                ret.push_back((char)(lo << 1 | 1));
            }
            ret.push_back('\0');
        }
        ret.pop_back();
        return ret;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> ret = {""};
        bool odd = 0;
        for(char ch: s) {
            if(ch == '\0') {
                ret.push_back("");
                odd = 0;
                continue;
            }
            int val = (ch >> 1) & 15;
            if(odd) {
                int pre = ret.back().back();
                ret.back().back() = pre << 4 | val;
            } else {
                ret.back().push_back(val);
            }
            odd = !odd;
        }
        return ret;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
