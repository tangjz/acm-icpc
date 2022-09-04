class Solution {
public:
    bool isValid(string_view code) {
        auto isValidTag = [&](string_view s) -> bool {
            if(s.empty() || s.size() >= 10)
                return 0;
            for(char ch: s)
                if(!isalpha(ch) || toupper(ch) != ch)
                    return 0;
            return 1;
        };
        auto hasSuffix = [&](string_view s, string_view t) -> bool {
            if(s.size() < t.size())
                return 0;
            return s.substr(s.size() - t.size()) == t;
        };
        int n = code.size();
        auto u = code.find('<'), v = code.find('>');
        if(u != 0 || v == string::npos)
            return 0;
        string_view tag = code.substr(u + 1, v - u - 1);
        if(!isValidTag(tag) || !hasSuffix(code, "</" + (string)tag + ">"))
            return 0;
        stack<string_view> stk;
        for(int i = 0; i < n; ) {
            if(i > 0 && stk.empty())
                return 0;
            if(code[i] != '<') {
                ++i;
                continue;
            }
            if(code.substr(i, 9) == "<![CDATA[") {
                auto j = code.find("]]>", i + 9);
                if(j == string::npos)
                    return 0;
                i = j + 3;
                continue;
            }
            if(code.substr(i, 2) == "</") {
                auto j = code.find(">", i + 2);
                if(j == string::npos)
                    return 0;
                tag = code.substr(i + 2, j - i - 2);
                if(!isValidTag(tag) || stk.empty() || stk.top() != tag)
                    return 0;
                stk.pop();
                i = j + 1;
                continue;
            }
            auto j = code.find(">", i + 1);
            if(j == string::npos)
                return 0;
            tag = code.substr(i + 1, j - i - 1);
            if(!isValidTag(tag))
                return 0;
            stk.push(tag);
            i = j + 1;
        }
        return stk.empty();
    }
};
