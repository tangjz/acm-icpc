class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int n = sentence.size();
        vector<int> psum = {0};
        for(auto &buf: sentence)
            psum.push_back(psum.back() + 1 + buf.size());
        int cnt = 0, pos = 0;
        ++cols;
        while(rows--) {
            int rem = cols;
            if(pos > 0 && rem >= psum[n] - psum[pos]) {
                rem -= psum[n] - psum[pos];
                ++cnt;
                pos = 0;
            }
            if(rem >= psum[n]) {
                cnt += rem / psum[n];
                rem %= psum[n];
            }
            pos = upper_bound(psum.begin(), psum.end(), rem + psum[pos]) - psum.begin() - 1;
        }
        return cnt;
    }
};
