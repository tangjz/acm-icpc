class Solution {
public:
    string maskPII(string s) {
        auto pos = s.find('@');
        if(pos != string::npos) {
            string name = s.substr(0, pos);
            if(name.size() > 1) {
                char fir = name[0], las = name.back();
                name = "";
                name.push_back(fir);
                name += "*****";
                name.push_back(las);
            }
            name += s.substr(pos);
            for(char &ch: name)
                ch = tolower(ch);
            return name;
        }
        string digit = "";
        for(char ch: s)
            if(isdigit(ch))
                digit.push_back(ch);
        int n = digit.size();
        s = "***-***-" + digit.substr(n - 4);
        if(n > 10) {
            digit = "+";
            for(int i = 10; i < n; ++i)
                digit.push_back('*');
            digit.push_back('-');
            s = digit + s;
        }
        return s;
    }
};
