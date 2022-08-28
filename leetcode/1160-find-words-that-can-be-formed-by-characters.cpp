class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        int ans = 0;
        unordered_map<char, int> ctr, upp;
        for(char ch: chars)
            ++upp[ch];
        for(auto &buf: words) {
            bool ban = 0;
            ctr.clear();
            for(char ch: buf)
                if((++ctr[ch]) > upp[ch]) {
                    ban = 1;
                    break;
                }
            if(!ban)
                ans += buf.size();
        }
        return ans;
    }
};
