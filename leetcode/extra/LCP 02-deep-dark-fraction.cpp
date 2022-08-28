class Solution {
public:
    vector<int> fraction(vector<int>& cont) {
        int fz = cont.back(), fm = 1;
        cont.pop_back();
        while(!cont.empty()) {
            tie(fz, fm) = make_pair(cont.back() * fz + fm, fz);
            cont.pop_back();
        }
        return {fz, fm};
    }
};
