class Solution {
public:
    vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
        vector<string> ret;
        for(auto &buf: words) {
            int las = 0, n = buf.size();
            for(int i = 0; i < n; ++i)
                if(buf[i] == separator) {
                    if(las < i)
                        ret.push_back(buf.substr(las, i - las));
                    las = i + 1;
                }
            if(las < n)
                ret.push_back(buf.substr(las));
        }
        return ret;
    }
};
