class Tinder {
    struct User {
        int gender, genderTo;
        int age, ageToLow, ageToUpp;
        set<string> tag;
    };

    map<int, User> usr;

public:
    Tinder() {
        
    }

    void signup(int userId, int gender, int preferredGender, int age, int minPreferredAge, int maxPreferredAge, vector<string> interests) {
        usr[userId] = (User){
            gender, preferredGender,
            age, minPreferredAge, maxPreferredAge,
            set<string>(interests.begin(), interests.end()),
        };
    }

    vector<int> getMatches(int userId) {
        User &cur = usr[userId];
        vector<pair<int, int> > seq;
        for(auto &it: usr) {
            if(it.first == userId)
                continue;
            User &nxt = it.second;
            if(cur.genderTo != nxt.gender)
                continue;
            if(cur.ageToLow > nxt.age || nxt.age > cur.ageToUpp)
                continue;
            int cnt = 0;
            for(auto &jt: cur.tag)
                cnt += nxt.tag.count(jt);
            if(cnt)
                seq.push_back({-cnt, it.first});
        }
        static const int maxd = 5;
        if(seq.size() > maxd) {
            nth_element(seq.begin(), seq.begin() + (maxd - 1), seq.end());
            seq.resize(maxd);
        }
        sort(seq.begin(), seq.end());
        vector<int> ret;
        for(auto &it: seq)
            ret.push_back(it.second);
        return ret;
    }
};

/**
 * Your Tinder object will be instantiated and called as such:
 * Tinder* obj = new Tinder();
 * obj->signup(userId,gender,preferredGender,age,minPreferredAge,maxPreferredAge,interests);
 * vector<int> param_2 = obj->getMatches(userId);
 */
