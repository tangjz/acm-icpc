class Twitter {
    static const int maxv = 501;
    int tim;
    unordered_map<int, bitset<maxv> > e;
    unordered_map<int, vector<pair<int, int> > > seq;
public:
    Twitter() {
        tim = 0;
        e.clear();
        seq.clear();
    }
    
    void postTweet(int userId, int tweetId) {
        seq[userId].push_back({++tim, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        static const int maxm = 10;
        vector<int> ret;
        set<pair<int, pair<int, int> > > que;
        auto upd = [&](int uid, int tid) {
            auto &vec = seq[uid];
            if(tid >= 0 && tid <= vec.size())
                que.insert({vec[tid].first, {uid, tid}});
            if(que.size() + ret.size() > maxm)
                que.erase(que.begin());
        };
        auto init = [&](int uid) {
            auto it = seq.find(uid);
            if(it != seq.end())
                upd(uid, (it -> second).size() - 1);
        };
        init(userId);
        auto it = e.find(userId);
        if(it != e.end()) {
            auto &vec = it -> second;
            for(int vid = vec._Find_first(); vid < (int)vec.size(); vid = vec._Find_next(vid))
                init(vid);
        }
        while(ret.size() < maxm && !que.empty()) {
            int uid, tid;
            tie(uid, tid) = que.rbegin() -> second;
            que.erase(*que.rbegin());
            ret.push_back(seq[uid][tid].second);
            upd(uid, tid - 1);
        }
        return ret;
    }
    
    void follow(int followerId, int followeeId) {
        if(followerId != followeeId)
            e[followerId].set(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        e[followerId].reset(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
