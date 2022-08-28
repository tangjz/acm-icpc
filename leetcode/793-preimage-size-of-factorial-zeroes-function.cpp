class Solution {
public:
    int preimageSizeFZF(int k) {
        typedef long long LL;
        vector<LL> seq = {1};
        while(seq.back() < k)
            seq.push_back(seq.back() * 5 + 1);
        while(!seq.empty()) {
            int rem = k / seq.back();
            if(rem == 5) // should addon, but will cause k' > k
                return 0;
            k %= seq.back();
            seq.pop_back();
        }
        return 5;
    }
};
