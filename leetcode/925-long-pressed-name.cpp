class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        auto calc = [&](string &buf) {
            vector<pair<char, int> > ret;
            for(char ch: buf)
                if(ret.empty() || ch != ret.back().first) {
                    ret.push_back({ch, 1});
                } else {
                    ++ret.back().second;
                }
            return ret;
        };
        vector<pair<char, int> > tmp = calc(name), pat = calc(typed);
        bool ban = pat.size() != tmp.size();
        for(int i = 0; !ban && i < pat.size(); ++i)
            ban |= pat[i].first != tmp[i].first || pat[i].second < tmp[i].second;
        return !ban;
    }
};
