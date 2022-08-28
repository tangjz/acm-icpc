class Solution {
public:
    int coopDevelop(vector<vector<int>>& skills) {
        typedef long long LL;
        int n = skills.size();
        vector<LL> msks;
        msks.reserve(n);
        for(auto &vec: skills) {
            LL msk = 0;
            sort(vec.begin(), vec.end());
            for(int x: vec)
                msk = msk << 10 | x;
            msks.push_back(msk);
        }
        sort(msks.begin(), msks.end());
        LL ans = n * (n - 1LL) / 2;
        unordered_map<LL, int> ctr;
        for(LL msk: msks) {
            vector<int> vec;
            for(LL rem = msk; rem > 0; vec.push_back(rem & 1023), rem >>= 10);
            reverse(vec.begin(), vec.end());
            int m = vec.size();
            for(int i = 1; i < (1 << m); ++i) {
                LL sub = 0;
                for(int j = 0; j < m; ++j)
                    if((i >> j) & 1)
                        sub = sub << 10 | vec[j];
                auto it = ctr.find(sub);
                if(it != ctr.end())
                    ans -= it -> second;
            }
            ++ctr[msk];
        }
        return ans % ((int)1e9 + 7);
    }
};
