/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
    map<pair<int, int>, int> Hash;
    bool cachedKnows(int a, int b) {
        pair<int, int> key = {a, b};
        auto it = Hash.find(key);
        if(it == Hash.end())
            return Hash[key] = knows(a, b);
        return it -> second;
    }
public:
    int findCelebrity(int n) {
        Hash.clear();
        int pos = 0;
        for(int i = 1; i < n; ++i)
            if(cachedKnows(pos, i))
                pos = i;
        for(int i = 0; i < n; ++i) {
            if(i == pos)
                continue;
            if(!cachedKnows(i, pos) || cachedKnows(pos, i))
                return -1;
        }
        return pos;
    }
};
