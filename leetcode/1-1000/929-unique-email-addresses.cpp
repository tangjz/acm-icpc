class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> ret;
        for(auto &email: emails) {
            auto u = email.find('@');
            string local = email.substr(0, u);
            auto v = local.find('+');
            if(v != string::npos)
                local.resize(v);
            int tot = 0;
            for(char ch: local)
                if(ch != '.')
                    local[tot++] = ch;
            local.resize(tot);
            ret.insert(local + email.substr(u));
        }
        return ret.size();
    }
};
