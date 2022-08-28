class Solution {
public:
    string reformat(string s) {
        string a = "", b = "";
        for(char ch : s)
            if(ch >= '0' && ch <= '9')
                a += ch;
            else
                b += ch;
        if(a.size() < b.size())
            swap(a, b);
        string t = "";
        if(a.size() - b.size() <= 1) {
            string::iterator it = a.begin(), jt = b.begin();
            while(it != a.end()) {
                t += *(it++);
                if(jt != b.end())
                    t += *(jt++);
            }
        }
        return t;
    }
};
