class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int pos = 0;
        auto fir = strs.front();
        while(true) {
            bool good = 1;
            char ch = pos < fir.size() ? fir[pos] : '\0';
            for(auto &it: strs)
                if(pos >= (int)it.size() || ch != it[pos]) {
                    good = 0;
                    break;
                }
            if(!good)
                break;
            ++pos;
        }
        return fir.substr(0, pos);
    }
};
