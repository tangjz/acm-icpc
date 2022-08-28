class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = (int)s.size();
        vector<int> psum = {0, 1};
        for(int i = 1; i < n; ++i) {
            if(s[i] != '0') {
                psum.push_back(psum.back());
                continue;
            }
            int j = i - minJump, k = max(i - maxJump, 0);
            psum.push_back(psum.back() + (k <= j && psum[j + 1] > psum[k]));
        }
        int tmp = psum.back();
        psum.pop_back();
        tmp -= psum.back();
        return tmp > 0;
    }
};
