class AuthenticationManager {
    int duration, counter;
    unordered_map<string, int> exp;
    queue<pair<int, string> > que;
public:
    AuthenticationManager(int timeToLive) {
        duration = timeToLive;
        counter = 0;
        unordered_map<string, int>().swap(exp);
        while(!que.empty())
            que.pop();
    }
    
    void generate(string tokenId, int currentTime) {
        exp[tokenId] = currentTime;
        que.push(make_pair(currentTime, tokenId));
        ++counter;
    }
    
    void renew(string tokenId, int currentTime) {
        auto it = exp.find(tokenId);
        if(it == exp.end() || (it -> second) + duration <= currentTime)
            return;
        exp[tokenId] = currentTime;
        que.push(make_pair(currentTime, tokenId));
    }
    
    int countUnexpiredTokens(int currentTime) {
        while(!que.empty() && que.front().first + duration <= currentTime) {
            string &tokenId = que.front().second;
            int &tim = que.front().first;
            if(exp[tokenId] == tim) {
                --counter;
                exp.erase(tokenId);
            }
            que.pop();
        }
        return counter;
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */
