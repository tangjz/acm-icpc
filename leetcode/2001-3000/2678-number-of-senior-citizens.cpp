class Solution {
public:
    int countSeniors(vector<string>& seq) {
        const int m = 15, q = 60;
        int ans = 0;
        for(auto &it: seq) {
            int age = stoi(it.substr(m - 4, 2));
            ans += age > q;
        }
        return ans;
    }
};
