class FileSharing {
    priority_queue<int> cand;
    unordered_map<int, set<int> > user, chunk;
public:
    FileSharing(int m) {
        cand.push(-1);
    }

    int join(vector<int> ownedChunks) {
        int uid = -cand.top();
        cand.pop();
        if(cand.empty())
            cand.push(-(uid + 1));
        for(int x: ownedChunks)
            if(user[uid].insert(x).second)
                chunk[x].insert(uid);
        return uid;
    }

    void leave(int userID) {
        for(int x: user[userID])
            chunk[x].erase(userID);
        user.erase(userID);
        cand.push(-userID);
    }

    vector<int> request(int userID, int chunkID) {
        bool needUpd = 1;
        vector<int> ret;
        for(int x: chunk[chunkID]) {
            needUpd &= x != userID;
            ret.push_back(x);
        }
        if(needUpd && ret.size() > 0) {
            user[userID].insert(chunkID);
            chunk[chunkID].insert(userID);
        }
        return move(ret);
    }
};

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing* obj = new FileSharing(m);
 * int param_1 = obj->join(ownedChunks);
 * obj->leave(userID);
 * vector<int> param_3 = obj->request(userID,chunkID);
 */
