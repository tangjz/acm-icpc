class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size(), ans = 0;
        set<pair<int, int> > sp;
        for(int i = 0; i < n; ++i)
            sp.insert({people[i], i});
        while(!sp.empty()) {
            pair<int, int> u = *sp.rbegin();
            sp.erase(u);
            if(!sp.empty()) {
                auto it = sp.lower_bound({limit - u.first + 1, 0});
                if(it != sp.begin()) {
                    pair<int, int> v = *(--it);
                    sp.erase(v);
                }
            }
            ++ans;
        }
        return ans;
    }
};
