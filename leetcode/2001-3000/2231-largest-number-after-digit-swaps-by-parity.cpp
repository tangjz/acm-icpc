class Solution {
public:
    int largestInteger(int num) {
        string rep = to_string(num);
        vector<int> seq[2];
        for(char ch: rep) {
            int o = ch - '0';
            seq[o & 1].push_back(o);
        }
        sort(seq[0].begin(), seq[0].end());
        sort(seq[1].begin(), seq[1].end());
        for(char &ch: rep) {
            int o = ch - '0';
            ch = seq[o & 1].back() + '0';
            seq[o & 1].pop_back();
        }
        return stoi(rep);
    }
};
