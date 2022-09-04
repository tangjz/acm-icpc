class Solution {
    vector<string_view> split(string_view s, char sep = '.') {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0; i < n; ++i) {
            int j = i;
            for( ; i < n && s[i] != sep; ++i);
            ret.push_back(s.substr(j, i - j));
        }
        if(n > 0 && s.back() == sep)
            ret.push_back(s.substr(n));
        return move(ret);
    }
    bool isIPv4(string_view IP) {
        vector<string_view> seq = split(IP, '.');
        if((int)seq.size() != 4)
            return 0;
        for(int i = 0; i < 4; ++i) {
            if(seq[i].empty() || (int)seq[i].size() > 3)
                return 0;
            int val = 0;
            for(char ch: seq[i]) {
                if(!isdigit(ch))
                    return 0;
                val = val * 10 + (ch - '0');
            }
            if(val < 0 || val >= 256 || to_string(val) != seq[i])
                return 0;
        }
        return 1;
    }
    bool isIPv6(string_view IP) {
        vector<string_view> seq = split(IP, ':');
        if((int)seq.size() != 8)
            return 0;
        for(int i = 0; i < 8; ++i) {
            if(seq[i].empty() || (int)seq[i].size() > 4)
                return 0;
            int val = 0;
            for(char ch: seq[i]) {
                int d;
                if(isdigit(ch)) {
                    d = ch - '0';
                } else if(isalpha(ch)) {
                    d = tolower(ch) - 'a' + 10;
                } else {
                    return 0;
                }
                if(d >= 16)
                    return 0;
                val = val * 16 + d;
            }
            if(val < 0 || val >= 65536)
                return 0;
        }
        return 1;
    }
public:
    string validIPAddress(string queryIP) {
        if(isIPv4(queryIP))
            return "IPv4";
        if(isIPv6(queryIP))
            return "IPv6";
        return "Neither";
    }
};
