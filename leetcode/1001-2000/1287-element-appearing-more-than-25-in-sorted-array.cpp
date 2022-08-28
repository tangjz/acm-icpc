class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        vector<pair<int, int> > seq;
        for(int x: arr) {
            auto it = seq.begin();
            for( ; it != seq.end() && it -> second != x; ++it);
            if(it != seq.end()) {
                ++(it -> first);
            } else if(seq.size() < 4) {
                seq.push_back({1, x});
            } else {
                --seq.back().first;
            }
            sort(seq.begin(), seq.end(), greater<pair<int, int> >());
            if(!seq.back().first)
                seq.pop_back();
        }
        return seq.front().second;
    }
};
