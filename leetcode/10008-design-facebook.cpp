class Facebook {
    int timestamp;
    map<int, vector<pair<int, string> > > pst;
    map<int, set<int> > fnd;
public:
    Facebook() {
    }

    void writePost(int userId, string postContent) {
        pst[userId].push_back({--timestamp, move(postContent)});
    }

    void addFriend(int user1, int user2) {
        fnd[user1].insert(user2);
        fnd[user2].insert(user1);
    }

    vector<string> showPosts(int userId) {
        vector<pair<int, string> > seq;
        for(int v: fnd[userId]) {
            auto &adt = pst[v];
            seq.insert(seq.end(), adt.begin(), adt.end());
        }
        sort(seq.begin(), seq.end());
        vector<string> ret;
        for(auto &it: seq)
            ret.push_back(it.second);
        return ret;
    }
};
