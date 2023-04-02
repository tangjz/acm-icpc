class TodoList {
    struct Task {
        int uid, due;
        string dsc;
        vector<string> tags;
    };
    vector<Task> seq;
    map<int, set<pair<int, int> > > taskByUser; // (due, taskId)
    map<pair<int, string>, set<pair<int, int> > > taskByUserTag; // (due, taskId)
public:
    TodoList() {
    }
   
    int addTask(int userId, string taskDescription, int dueDate, vector<string> tags) {
        pair<int, int> key = {dueDate, (int)seq.size()};
        taskByUser[userId].insert(key);
        for(auto tag: tags)
            taskByUserTag[{userId, tag}].insert(key);
        seq.push_back((Task){userId, dueDate, taskDescription, move(tags)});
        return (int)seq.size();
    }
   
    vector<string> getAllTasks(int userId) {
        vector<string> ret;
        auto it = taskByUser.find(userId);
        if(it != taskByUser.end())
            for(auto &jt: it -> second)
                ret.push_back(seq[jt.second].dsc);
        return ret;
    }
   
    vector<string> getTasksForTag(int userId, string tag) {
        vector<string> ret;
        auto it = taskByUserTag.find({userId, tag});
        if(it != taskByUserTag.end())
            for(auto &jt: it -> second)
                ret.push_back(seq[jt.second].dsc);
        return ret;
    }
   
    void completeTask(int userId, int taskId) {
        --taskId;
        if(taskId >= 0 && taskId < (int)seq.size() && seq[taskId].uid == userId) {
            pair<int, int> key = {seq[taskId].due, taskId};
            taskByUser[userId].erase(key);
            for(auto tag: seq[taskId].tags)
                taskByUserTag[{userId, tag}].erase(key);
        }
    }
};

/**
 * Your TodoList object will be instantiated and called as such:
 * TodoList* obj = new TodoList();
 * int param_1 = obj->addTask(userId,taskDescription,dueDate,tags);
 * vector<string> param_2 = obj->getAllTasks(userId);
 * vector<string> param_3 = obj->getTasksForTag(userId,tag);
 * obj->completeTask(userId,taskId);
 */
