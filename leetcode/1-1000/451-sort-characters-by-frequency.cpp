class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> ctr;
        vector<char> que;
        for(char ch : s) {
            auto it = ctr.find(ch);
            if(it != ctr.end()) {
                ++(it -> second);
            } else {
                ctr.insert(make_pair(ch, 1));
                que.push_back(ch);
            }
        }
        sort(que.begin(), que.end(), [&](char const &u, char const &v) -> bool {
            return ctr[u] > ctr[v];
        });
        string ret = "";
        for(char ch : que)
            for(int rem = ctr[ch]; rem > 0; --rem)
                ret += ch;
        return ret;
    }
};
