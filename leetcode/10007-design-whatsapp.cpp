class WhatsApp {
    unordered_map<int, vector<string> > msg;
    vector<set<int> > grp;
public:
    WhatsApp() {
        grp.push_back({});
    }

    void sendMessage(int toUser, string message) {
        msg[toUser].push_back(move(message));
    }

    int createGroup(vector<int> initialUsers) {
        int gId = grp.size();
        grp.push_back(set<int>(initialUsers.begin(), initialUsers.end()));
        return gId;
    }

    void addUserToGroup(int groupId, int userId) {
        if(groupId <= 0 || groupId >= (int)grp.size())
            return;
        grp[groupId].insert(userId);
    }

    void sendGroupMessage(int fromUser, int groupId, string message) {
        if(groupId <= 0 || groupId >= (int)grp.size() || !grp[groupId].count(fromUser))
            return;
        for(int toUser: grp[groupId])
            if(toUser != fromUser)
                msg[toUser].push_back(message);
    }

    vector<string> getMessagesForUser(int userId) {
        vector<string> ret = msg[userId];
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
